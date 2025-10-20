#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include "Geometry.hpp"
#include <algorithm>





int main()
{



	unsigned int width = 1200;
	unsigned int height = 800;
	sf::RenderWindow window(sf::VideoMode({ width, height }), "Opengl", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(165);

	bool isDragging = false;
	sf::Vector2f dragOffset;
	
	const float WINDOW_WIDTH = static_cast<float>(width);
	const float WINDOW_HEIGHT = static_cast<float>(height);



	std::vector<Rectangle> rectangles;
	rectangles.push_back(Rectangle{ 600.0f, 650.0f, 2000.0f, 300.0f, sf::Color::Blue, sf::Color::Cyan, 1.0f});


	std::vector<Ball> balls = {
		{600.0f, 400.0f, 50.0f, sf::Color::Black, sf::Color::White, 2.0f}
	};

	const float ballRadius = balls[0].radius;




	while (window.isOpen()) {

		while (auto event = window.pollEvent()) {

			if (event->is<sf::Event::Closed>()) {

				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
					window.close();
				}
			}








			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mouseButtonPressed->button == sf::Mouse::Button::Left)
				{
					sf::Vector2 mousePos = window.mapPixelToCoords({ 
						mouseButtonPressed->position.x,
						mouseButtonPressed->position.y 
					});

					if (balls[0].contains(mousePos)) {
						isDragging = true;

						dragOffset = mousePos - sf::Vector2f(balls[0].px, balls[0].py);
					}
				}
			}

			else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
			{
				if (mouseButtonReleased->button == sf::Mouse::Button::Left)
				{
					isDragging = false;
				}
			}

			else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
			{
				if (isDragging)
				{
					sf::Vector2f newMousePos = window.mapPixelToCoords({
						mouseMoved->position.x,
						mouseMoved->position.y 
					});


					float desired_px = newMousePos.x - dragOffset.x;
					float desired_py = newMousePos.y - dragOffset.y;

					balls[0].px = std::min(WINDOW_WIDTH - ballRadius, 
						std::max(ballRadius, desired_px));
					balls[0].py = std::min(WINDOW_HEIGHT - ballRadius, 
						std::max(ballRadius, desired_py));
				}
			}


			
		}
		// Render //////////////////////////////////////////////
		






		window.clear(sf::Color::Black);
		// Draw ///////////////////////////////////////////////



		for (const auto& rectangle : rectangles) {
			sf::RectangleShape rect = rectangle.createRectangle();
			window.draw(rect);
		}


		for (const auto& ball : balls) {
			sf::CircleShape circle = ball.createCircle();
			window.draw(circle);
		}

		
		
		
		
		
		
		////////////////////////////////////////////////////////////////
		window.display();
	}


	
	return 0;
}





/*


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath> // For std::sqrt

// --- Helper Structs ---

struct Ball {
	float px, py, vx, vy, ax, ay, radius;
	sf::Color fillColor;
	sf::Color outlineColor;
	float outlineThickness;

	Ball(float px_, float py_, float radius_,
		sf::Color fill = sf::Color::Black,
		sf::Color outline = sf::Color::White,
		float thickness = 1.0f)
		: px(px_), py(py_), vx(0), vy(0), ax(0), ay(0),
		radius(radius_), fillColor(fill), outlineColor(outline),
		outlineThickness(thickness) {
	}

	// Create an SFML circle from this ball
	sf::CircleShape createCircle() const {
		sf::CircleShape circle(radius);
		circle.setOrigin({ radius, radius }); // center the circle
		circle.setPosition({ px, py });
		circle.setFillColor(fillColor);
		circle.setOutlineColor(outlineColor);
		circle.setOutlineThickness(outlineThickness);
		return circle;
	}

	// Utility to check if a point is inside the ball
	bool contains(const sf::Vector2f& point) const {
		float dx = point.x - px;
		float dy = point.y - py;
		return std::sqrt(dx * dx + dy * dy) <= radius;
	}
};


struct Rectangle {
	float px, py;
	float width, height;
	sf::Color fillColor;
	sf::Color outlineColor;
	float outlineThickness;

	sf::RectangleShape createRectangle() const {
		sf::RectangleShape rectangle({ width, height });
		rectangle.setOrigin({ rectangle.getSize().x / 2.f, rectangle.getSize().y / 2.f });

		rectangle.setPosition({ px, py });
		rectangle.setFillColor(fillColor);
		rectangle.setOutlineColor(outlineColor);
		rectangle.setOutlineThickness(outlineThickness);

		return rectangle;
	}
};


// --- Main Function ---

int main()
{
	unsigned int width = 1200;
	unsigned int height = 800;
	sf::RenderWindow window(sf::VideoMode({ width, height }), "SFML Drag Ball", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(165);

	// --- State Variables for Dragging ---
	bool isDragging = false;
	sf::Vector2f dragOffset; // To store the mouse's offset from the ball's center

	// --- Scene Setup ---
	std::vector<Rectangle> rectangles;
	rectangles.push_back(Rectangle{ 600.0f, 650.0f, 2000.0f, 300.0f, sf::Color::Blue, sf::Color::Cyan, 1.0f });

	// We'll only be dealing with balls[0] for dragging in this example
	std::vector<Ball> balls = {
		{600.0f, 400.0f, 50.0f, sf::Color::Black, sf::Color::White, 2.0f}
	};

	// --- Game Loop ---
	while (window.isOpen()) {

		while (auto event = window.pollEvent()) {

			// --- Window Events ---
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
					window.close();
				}
			}


			// --- Mouse Button Pressed: Initiate Drag ---
			if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mouseButtonPressed->button == sf::Mouse::Button::Left)
				{
					// *** FIX: Use ->position.x and ->position.y ***
					sf::Vector2f mousePos = window.mapPixelToCoords({ mouseButtonPressed->position.x, mouseButtonPressed->position.y });

					// Check if the click is within the ball's bounds
					if (balls[0].contains(mousePos)) {
						isDragging = true;

						// Calculate the offset between the mouse click and the ball's center
						// This prevents the ball from "jumping" when the drag starts.
						dragOffset = mousePos - sf::Vector2f(balls[0].px, balls[0].py);
					}
				}
			}

			// --- Mouse Button Released: End Drag ---
			else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
			{
				if (mouseButtonReleased->button == sf::Mouse::Button::Left)
				{
					isDragging = false;
				}
			}

			// --- Mouse Moved: Perform Dragging ---
			else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
			{
				if (isDragging)
				{
					// *** FIX: Use ->position.x and ->position.y ***
					sf::Vector2f newMousePos = window.mapPixelToCoords({ mouseMoved->position.x, mouseMoved->position.y });

					// Calculate the new ball position by subtracting the stored offset
					balls[0].px = newMousePos.x - dragOffset.x;
					balls[0].py = newMousePos.y - dragOffset.y;
				}
			}

		}


		// --- Render ---
		window.clear(sf::Color::Black);

		// Draw Rectangles
		for (const auto& rectangle : rectangles) {
			sf::RectangleShape rect = rectangle.createRectangle();
			window.draw(rect);
		}

		// Draw Balls
		for (const auto& ball : balls) {
			sf::CircleShape circle = ball.createCircle();
			window.draw(circle);
		}

		window.display();
	}

	return 0;
}


*/






