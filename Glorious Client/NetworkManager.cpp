#include <thread>
#include <fstream>

#include "NetworkManager.hpp"
#include "Instance.hpp"

namespace NetworkManager {
	
	std::string ipAddress;
	sf::TcpSocket socket;
	sf::SocketSelector socketSelector;
	int identifier = 0;
	unsigned int port;
	bool connected = false;
	unsigned int ping;
	std::thread receivingThread;
	std::map<int, std::shared_ptr<Instance>> instanceMap;

	bool connect(std::string ipAddress, unsigned int port) {
		NetworkManager::ipAddress = ipAddress;
		NetworkManager::port = port;

		sf::Socket::Status status;

		status = socket.connect(ipAddress, (unsigned short)port, sf::seconds(3));
		if (status != sf::Socket::Done)
			connected = false;
		else
			connected = true;
		return connected;
	}

	bool disconnect() {
		connected = false;
		return true;
	}

	void receiveThread() {
		while (connected) {
			if (socketSelector.wait(sf::seconds(0.1f))) {
				sf::Packet incomingPacket;
				if (socket.receive(incomingPacket) == sf::Socket::Disconnected) {
					disconnect();
					//TODO: Load login screen
				}
				else {
					int identifier;
					incomingPacket >> identifier;
					if (identifier != -1) {
						//A local instance is expecting data back from server
						instanceMap[identifier]->packetBack(&incomingPacket);
					}
					else {
						//Generic message from server, handle accordingly
					}
				}
			}
		}
		socketSelector.clear();
		socket.disconnect();
	}

	void sendPacket(std::shared_ptr<sf::Packet> packet, std::shared_ptr<Instance> instance) {
		sf::Packet temp;
		if (instance != nullptr) {
			instanceMap[instance->getId()] = instance;
			temp << instance->getId();
			temp.append(packet->getData(), packet->getDataSize());
		}
		else {
			temp << -1;
			temp.append(packet->getData(), packet->getDataSize());
		}

		//For debugging purposes
		const void * a = temp.getData();
		char * b = (char*)a + 1;
		char be;
		unsigned int size = temp.getDataSize();
		std::ofstream myfile;
		myfile.open("client_debug.txt");
		for (int i = 0; i < size; i++) {
			b = (char*)a + i;
			be = *b;
			myfile << b;
		}
		myfile.close();
		socket.send(temp);
	}

	bool connectedToServer() {
		return connected;
	}
}