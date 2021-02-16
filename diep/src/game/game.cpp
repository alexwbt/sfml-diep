#include "game.h"

namespace diep
{
	Game::~Game()
	{
		for (auto object : objects_)
			delete object;
		for (auto object : spawn_list_)
			delete object;
		for (auto object : particles_)
			delete object;
	}

	void Game::SetData(sf::Packet& data)
	{
		
	}

	void Game::GetData(sf::Packet& data)
	{

	}

	void Game::Update(sf::Window& window)
	{
		particles_.remove_if([](object::Object* object)
		{
			object->Update();
			if (object->should_remove())
			{
				delete object;
				return true;
			}
			return false;
		});

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
				float dir = atan2f(mouse.y - win_height_ / 2.0f, mouse.x - win_width_ / 2.0f);
				tank->Turn(dir);
			}
			object->Update();
			if (focus_id_ == object->id())
			{
				cam_x_ = object->x();
				cam_y_ = object->y();
			}

			if (object->should_remove())
			{
				object->SetIsParticle(true);
				object->SetShouldRemove(false);
				particles_.push_back(object);
				return true;
			}
			return false;
		});
	}

	void Game::Render(sf::RenderTarget& target) const
	{
		const float grid_size = grid_size_ * scale_;
		const float grid_line_width = grid_line_width_ * scale_;

		for (float x = fmod(OnScreenX(0), grid_size); x < win_width_; x += grid_size)
		{
			sf::RectangleShape line(sf::Vector2f(grid_line_width, (float)win_height_));
			line.setPosition(x, -grid_line_width / 2.0f);
			line.setFillColor(sf::Color(200, 200, 200, 255));
			target.draw(line);
		}
		for (float y = fmod(OnScreenY(0), grid_size); y < (float)win_height_; y += grid_size)
		{
			sf::RectangleShape line(sf::Vector2f((float)win_width_, grid_line_width));
			line.setPosition(-grid_line_width / 2.0f, y);
			line.setFillColor(sf::Color(200, 200, 200, 255));
			target.draw(line);
		}

		sf::RenderTexture texture;
		texture.create(win_width_, win_height_);

		auto render_obj = [&](object::Object* obj)
		{
			if (obj->opacity() == 255)
				obj->Render(target);
			else
			{
				texture.clear(sf::Color(0, 0, 0, 0));
				obj->Render(texture);

				sf::Sprite sprite(texture.getTexture());
				sprite.setTextureRect(sf::IntRect(0, win_height_, win_width_, -(int)win_height_));
				sprite.setColor(sf::Color(255, 255, 255, obj->opacity()));
				target.draw(sprite);
			}
		};

		for (auto obj : objects_)
			render_obj(obj);
		for (auto par : particles_)
			render_obj(par);
	}

	void Game::SetWindowSize(const sf::Vector2u& size)
	{
		win_width_ = size.x;
		win_height_ = size.y;
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
