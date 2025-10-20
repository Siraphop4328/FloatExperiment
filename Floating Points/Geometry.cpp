#include "Geometry.hpp"
#include <cmath>
#include <iostream>

// --- Ball Implementations ---

// Constructor Definition
Ball::Ball(float px_, float py_, float radius_, sf::Color fill, sf::Color outline, float thickness)
	: px(px_), py(py_), vx(0), vy(0), ax(0), ay(0),
	radius(radius_), fillColor(fill), outlineColor(outline),
	outlineThickness(thickness) {
}

// createCircle Implementation
sf::CircleShape Ball::createCircle() const {
	sf::CircleShape circle(radius);
	circle.setOrigin({ radius, radius }); // center the circle
	circle.setPosition({ px, py });
	circle.setFillColor(fillColor);
	circle.setOutlineColor(outlineColor);
	circle.setOutlineThickness(outlineThickness);
	return circle;
}

// contains Implementation (Hit Detection)
bool Ball::contains(const sf::Vector2f& point) const {
	float dx = point.x - px;
	float dy = point.y - py;
	return std::sqrt(dx * dx + dy * dy) <= radius;
}


// --- Rectangle Implementations ---

// createRectangle Implementation
sf::RectangleShape Rectangle::createRectangle() const {
	sf::RectangleShape rectangle({ width, height });
	rectangle.setOrigin({ rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f });

	rectangle.setPosition({ px, py });
	rectangle.setFillColor(fillColor);
	rectangle.setOutlineColor(outlineColor);
	rectangle.setOutlineThickness(outlineThickness);

	return rectangle;
}