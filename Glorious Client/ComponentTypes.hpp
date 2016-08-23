#pragma once
using ComponentType = unsigned int;

#define N_COMPONENT_TYPES 3

enum class Component {
	Drawable = 0, Updateable, Network, Input
};