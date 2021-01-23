#include "game.h"

namespace diep
{
	Game::~Game()
	{
		for (const object::Object* object : objects_)
			delete object;
	}

	void Game::Update(sf::Window& window)
	{
		objects_.splice(objects_.begin(), spawn_list_);
		spawn_list_.clear();
		objects_.remove_if([this, &window](object::Object* object)
		{
			if (control_id_ == object->id() && object->type() == object::Type::kTank)
			{
				object::Tank* tank = (object::Tank*)object;
				bool controls[object::Tank::kControlListSize] =
				{
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W),
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A),
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S),
					sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D),
					sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
				};
				tank->SetControls(controls);

				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				float dir = atan2(mouse.y - win_height_ / 2, mouse.x - win_width_ / 2);
				tank->Turn(dir);
			}
			object->Update();
			if (focus_id_ == object->id())
			{
				cam_x_ = object->x();
				cam_y_ = object->y();
			}

			return object->should_remove();
		});
	}

	void Game::Render(sf::RenderTarget& target) const
	{
		const float grid_size = grid_size_ * scale_;
		const float grid_line_width = grid_line_width_ * scale_;

		for (float x = fmod(OnScreenX(0), grid_size); x < win_width_; x += grid_size)
		{
			sf::RectangleShape line(sf::Vector2f(grid_line_width, win_height_));
			line.setPosition(x, -grid_line_width / 2.0f);
			line.setFillColor(sf::Color(200, 200, 200, 255));
			target.draw(line);
		}
		for (float y = fmod(OnScreenY(0), grid_size); y < win_height_; y += grid_size)
		{
			sf::RectangleShape line(sf::Vector2f(win_width_, grid_line_width));
			line.setPosition(-grid_line_width / 2.0f, y);
			line.setFillColor(sf::Color(200, 200, 200, 255));
			target.draw(line);
		}

		sf::RenderTexture texture;
		texture.setSmooth(true);
		texture.create(win_width_, win_height_);

		for (const object::Object* object : objects_)
		{
			if (object->opacity() == 255)
				object->Render(target);
			else
			{
				texture.clear(sf::Color(0, 0, 0, 0));
				object->Render(texture);

				sf::Sprite sprite(texture.getTexture());
				sprite.setTextureRect(sf::IntRect(0, win_height_, win_width_, -win_height_));
				sprite.setColor(sf::Color(255, 255, 255, object->opacity()));
				target.draw(sprite);
			}
		}
	}

	void Game::SetWindowSize(const sf::Vector2u& size)
	{
		win_width_ = (float)size.x;
		win_height_ = (float)size.y;
	}

	void Game::Spawn(object::Object* obj)
	{
		spawn_list_.push_front(obj);
	}

	void Game::KeyPressed(int key)
	{
		switch (key)
		{
		case sf::Keyboard::Key::F1:
			debug_ = !debug_;
			break;
		}
	}
}
