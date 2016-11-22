#pragma once

#include <SFML/Graphics.hpp>
#include "OrientedBoundingBox.h"

class CollisionDetector
{
public:
	bool static collision(const sf::Sprite& object1, const sf::Sprite& object2);
};
