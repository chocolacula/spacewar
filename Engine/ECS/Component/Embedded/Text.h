#pragma once
#include <string>

#include "../../../Types/Color.h"
#include "../Component.h"

class Text final : public Component
{
public:
	Text(Entity* entity) :
		Component(entity),
		color(Color3::LIGHT_BLUE)
	{}

	Color3 color;
	std::string value;
};
