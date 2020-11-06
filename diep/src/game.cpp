#include "game.h"

namespace diep
{
	Game::~Game()
	{
		for (const Object* object : objects_)
			delete object;
	}

	void Game::Update(float time_scale)
	{
		for (Object* object : objects_)
		{
			if (control_id_ == object->Id() && object->Type() == Type::kTank)
			{
				bool controls[4] =
				{
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W),
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A),
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S),
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
				};
				((Tank*)object)->SetControls(controls);
			}
			object->Update(time_scale);
			if (focus_id_ == object->Id())
			{
				cam_x_ = object->X();
				cam_y_ = object->Y();
			}
		}
	}

	void Game::Render(sf::RenderWindow& window) const
	{
		const float grid_size = grid_size_ * scale_;
		const float grid_line_width = grid_line_width_ * scale_;

		for (float x = fmod(OnScreenX(0), grid_size); x < win_width_; x += grid_size) {
			sf::RectangleShape line(sf::Vector2f(grid_line_width, win_height_));
			line.setPosition(x, -grid_line_width / 2.0f);
			line.setFillColor(sf::Color(200, 200, 200, 255));
			window.draw(line);
		}
		for (float y = fmod(OnScreenY(0), grid_size); y < win_height_; y += grid_size) {
			sf::RectangleShape line(sf::Vector2f(win_width_, grid_line_width));
			line.setPosition(-grid_line_width / 2.0f, y);
			line.setFillColor(sf::Color(200, 200, 200, 255));
			window.draw(line);
		}

		for (const Object* object : objects_)
			object->Render(window);
	}

	void Game::SetWindowSize(const sf::Vector2u& size)
	{
		win_width_ = size.x;
		win_height_ = size.y;
	}
}