#pragma once
#include <sstream>
#include "ComponentTypes.hpp"

class C_Base {
public:
	C_Base(const Component type) : type(type) {}
	virtual ~C_Base() {}

	Component getType() { return type; }

	friend std::stringstream& operator >> (
		std::stringstream& stream, C_Base& b) {
		b.ReadIn(stream);
		return stream;
	}

	virtual void ReadIn(std::stringstream* stream) = 0;

protected:
	Component type;
};