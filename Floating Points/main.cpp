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











