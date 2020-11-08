#include <SFML/Graphics.hpp>
#include <chrono>

#include "game.h"

int main()
{
	using namespace std::chrono;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Diep", sf::Style::Default, sf::ContextSettings(0, 0, 10, 1, 1));

	diep::Game& game = diep::Game::Instance();
	game.SetWindowSize(window.getSize());

	auto start_time = high_resolution_clock::now();
	double delta_time = 0.0;
	constexpr double time_step = 1000000000.0 / 60.0;

	auto update_timer = high_resolution_clock::now();
	int update_counter = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
				game.SetWindowSize(sf::Vector2u(event.size.width, event.size.height));
				break;
			case sf::Event::MouseWheelMoved:
				game.Scale(game.Scale() + event.mouseWheel.delta);
				break;
			default: break;
			}
		}

		auto now = high_resolution_clock::now();
		delta_time += (double)duration_cast<nanoseconds>(now - start_time).count() / time_step;
		start_time = now;

		bool should_update = delta_time > 1;
		while (delta_time >= 1)
		{
			game.Update(window);
			update_counter++;
			delta_time--;
		}

		if (should_update)
		{
			window.clear(sf::Color(240, 240, 240, 255));
			game.Render(window);
			window.display();
		}

		if (duration_cast<nanoseconds>(now - update_timer).count() >= 1000000000)
		{
			window.setTitle("Diep | ups: " + std::to_string(update_counter));
			update_counter = 0;
			update_timer = now;
		}
	}

	return 0;
}
