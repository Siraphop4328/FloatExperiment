#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include "Geometry.hpp" 
#include <algorithm>
#include <sstream>
#include <iomanip> 

int main()
{
	unsigned int width = 1200;
	unsigned int height = 800;
	sf::RenderWindow window(sf::VideoMode({ width, height }), "Opengl", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(240);

	bool isDragging = false;
	sf::Vector2f dragOffset;

	const float WINDOW_WIDTH = static_cast<float>(width);
	const float WINDOW_HEIGHT = static_cast<float>(height);

	std::vector<Rectangle> rectangles;
	rectangles.push_back(Rectangle{ 600.0f, 650.0f, 2000.0f, 300.0f, sf::Color::Blue, sf::Color::Cyan, 1.0f });

	std::vector<Ball> balls = {
		{60.0f, 400.0f, 50.0f, sf::Color::Black, sf::Color::White, 2.0f},
		//{210.0f, 400.0f, 50.0f, sf::Color::Black, sf::Color::White, 2.0f}

	};

	// Clock for frame time calculation (delta time)
	sf::Clock frameClock;
	// Clock for controlling how often the FPS text is updated
	sf::Clock updateClock;

	// Variables for FPS calculation over an interval
	int frameCount = 0;
	float currentFPS = 0.0f;
	const sf::Time FPS_UPDATE_INTERVAL = sf::seconds(0.05f); // Update every what second

	sf::Font font;

	if (!font.openFromFile("Font1.ttf")) {
		return -1;
	}
	
	sf::Text fpsText(font, "Hello World", 100);
	fpsText.setCharacterSize(24);
	fpsText.setFillColor(sf::Color::Green);
	fpsText.setPosition({ 10.f, 10.f });

	const float ballRadius = balls[0].radius;

	int draggedBallIndex = -1;

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


			else if (const auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
				sf::Vector2f mousePos = window.mapPixelToCoords({ e->position.x, e->position.y });
				balls[0].onMousePressed(mousePos);
			}
			else if (const auto* e = event->getIf<sf::Event::MouseButtonReleased>()) {
				balls[0].onMouseReleased();
			}
			else if (const auto* e = event->getIf<sf::Event::MouseMoved>()) {
				sf::Vector2f mousePos = window.mapPixelToCoords({ e->position.x, e->position.y });
				balls[0].onMouseMoved(mousePos, WINDOW_WIDTH, WINDOW_HEIGHT);
			}
		}

		// Calculate Frame Time (Delta Time)
		sf::Time elapsed = frameClock.restart();
		float frameTime = elapsed.asSeconds();

		// Increment Frame Counter
		frameCount++;

		// Check if it's time to update the FPS text
		if (updateClock.getElapsedTime() >= FPS_UPDATE_INTERVAL) {

			// Calculate FPS as: (Total Frames) / (Total Time Elapsed)
			currentFPS = static_cast<float>(frameCount) / updateClock.getElapsedTime().asSeconds();

			// Format and set the new string
			std::ostringstream ss;
			ss << "FPS: " << std::fixed << std::setprecision(0) << currentFPS; // Display as integer
			fpsText.setString(ss.str());

			// Reset the counter and the clock for the next interval
			frameCount = 0;
			updateClock.restart();
		}

		

		// Render /////////////////////////////////////////////////////////////////////////////////
		window.clear(sf::Color::Black);
		// Draw //////////////////////////////////////////////////////////////////

		for (const auto& rectangle : rectangles) {
			sf::RectangleShape rect = rectangle.createRectangle();
			window.draw(rect);
		}

		for (const auto& ball : balls) {
			sf::CircleShape circle = ball.createCircle();
			window.draw(circle);
		}

		window.draw(fpsText);
		////////////////////////////////////////////////////////////////
		window.display();
	}
	return 0;
}
