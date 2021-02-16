#include <chrono>
#include <iostream>

//#include <SFML/Network.hpp>

#include "game/game.h"

//int main()
//{
//	sf::UdpSocket socket;
//	uint16_t port = 34437;
//	if (socket.bind(port) != sf::Socket::Done)
//	{
//		std::cout << "Failed to bind port " << std::endl;
//		exit(1);
//	}
//
//	sf::Packet packet;
//	std::string message = "Hello World";
//	packet << message;
//
//	socket.send(packet, sf::IpAddress::Broadcast, port + 1);
//}

//int main()
//{
//	sf::UdpSocket socket;
//	uint16_t port = 34437;
//	if (socket.bind(port) != sf::Socket::Done)
//	{
//		std::cout << "Failed to bind port " << std::endl;
//		exit(1);
//	}
//
//	sf::Packet packet;
//	auto addr = sf::IpAddress::Any;
//	uint16_t res_port = 34437;
//	socket.receive(packet, addr, res_port);
//	
//	std::string message;
//	packet >> message;
//
//	std::cout << "Received: " << message << std::endl;
//
//	system("pause");
//}

int main()
{
	using namespace std::chrono;
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Diep", sf::Style::Default, sf::ContextSettings(0, 0, 10));

	diep::Game game;
	game.SetWindowSize(window.getSize());

	// spawn objects
	auto player_id = game.NextId();
	game.Spawn(new diep::object::Tank(game, player_id, 0, 0, 10));
	game.SetFocus(player_id);
	game.SetControl(player_id);

	//diep::object::Tank* tank = new diep::object::Tank(game, game.NextId(), 300, 0, 10);
	//bool ctrls[diep::object::Tank::kControlListSize] = { false, true, false, false, false };
	//tank->SetControls(ctrls);
	//game.Spawn(tank);

	srand((unsigned int)time(0));
	for (int i = 0; i < 50; i++)
	{
		float x = rand() % 2000 - 1000.0f;
		float y = rand() % 2000 - 1000.0f;
		float r = rand() % 50 + 10.0f;
		uint8_t p = rand() % 3 + 3;
		auto obj = new diep::object::Object(game, game.NextId(), x, y, r, p);
		game.Spawn(obj);
	}

	// game loop
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
			case sf::Event::KeyPressed:
				game.KeyPressed(event.key.code);
				break;
			default: break;
			}
		}

		auto now = high_resolution_clock::now();
		delta_time += (double)duration_cast<nanoseconds>(now - start_time).count() / time_step;
		start_time = now;

		bool should_update = delta_time >= 1;
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
