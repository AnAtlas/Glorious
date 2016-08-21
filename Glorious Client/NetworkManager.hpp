#pragma once
#include <SFML/Network.hpp>
#include <memory>

class Instance;

namespace Network {
	extern bool connect(std::string ipAddress, unsigned int port);
	extern bool disconnect();
	extern void sendPacket(std::shared_ptr<sf::Packet> packet, std::shared_ptr<Instance> instance = nullptr);
	extern bool connectedToServer();
}