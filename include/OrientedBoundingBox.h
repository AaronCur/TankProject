#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// Collision detection routine taken from the SFML wiki:
/// https://github.com/SFML/SFML/wiki/Source%3A-Simple-Collision-Detection-for-SFML-2
/// </summary>
class OrientedBoundingBox // Used in the BoundingBoxTest
{
public:
	OrientedBoundingBox(const sf::Sprite& Object); // Calculate the four points of the OBB from a transformed (scaled, rotated...) RectangleShape

	sf::Vector2f Points[4];

	void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max); // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
};
