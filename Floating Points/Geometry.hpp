#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

struct Ball {
	float px, py, vx, vy, ax, ay, radius;
	sf::Color fillColor;
	sf::Color outlineColor;
	float outlineThickness;

	// Constructor definition (must be here as it initializes members)
	Ball(float px_, float py_, float radius_,
		sf::Color fill = sf::Color::Black,
		sf::Color outline = sf::Color::White,
		float thickness = 1.0f);

	// Method declarations (implementation in Geometry.cpp)
	sf::CircleShape createCircle() const;
	bool contains(const sf::Vector2f& point) const;
};


struct Rectangle {
	float px, py;
	float width, height;
	sf::Color fillColor;
	sf::Color outlineColor;
	float outlineThickness;

	// Method declaration
	sf::RectangleShape createRectangle() const;
};
