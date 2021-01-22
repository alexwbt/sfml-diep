#include "../game.h"

namespace diep
{
	namespace object
	{
		void Object::Push(float x, float y)
		{
			vel_x_ += x;
			vel_y_ += y;
		}

		void Object::Update()
		{
			x_ += vel_x_;
			y_ += vel_y_;
			for (Object* obj : game.Objects())
			{
				if (obj->id_ != id_ &&
					obj->team_ != team_ &&
					coll::collide(*this, *obj))
				{
					health_ -= obj->body_damage_;
					float dir = atan2(y_ - obj->y_, x_ - obj->x_);
					Push(cos(dir), sin(dir));
					break;
				}
			}

			if (health_ <= 0)
				should_remove_ = true;

			if (id_ == 1)
			opacity_--;
		}

		bool Object::OnScreen() const
		{
			// TODO: proper on screen function
			return true;
		}

		void Object::Render(sf::RenderTarget& target) const
		{
			float radius = radius_ * game.Scale();
			float screen_x = game.OnScreenX(x_);
			float screen_y = game.OnScreenY(y_);

			sf::CircleShape border(radius, 100);
			border.setFillColor(border_color_);

			float body_radius = radius - game.Scale();
			sf::CircleShape body(body_radius, 100);
			body.setFillColor(color_);

			if (opacity_ == 255)
			{
				border.setPosition(sf::Vector2f(screen_x - radius, screen_y - radius));
				body.setPosition(sf::Vector2f(screen_x - body_radius, screen_y - body_radius));
				target.draw(border);
				target.draw(body);
			}
			else
			{
				sf::RenderTexture texture;
				unsigned int size = int(radius * 2);
				texture.create(size, size);
				texture.draw(border);
				body.setPosition(sf::Vector2f(game.Scale(), game.Scale()));
				texture.draw(body);

				sf::Sprite sprite(texture.getTexture());
				sprite.setPosition(sf::Vector2f(screen_x - radius, screen_y - radius));
				sprite.setColor(sf::Color(255, 255, 255, opacity_));
				target.draw(sprite);
			}

			// render health
			if (render_health_ && health_ < max_health_ && opacity_ == 255)
			{
				sf::RectangleShape max_health_bar(sf::Vector2f(radius * 2.0f, 8));
				max_health_bar.setPosition(screen_x - radius, screen_y + radius * 1.2f);
				max_health_bar.setFillColor(sf::Color(0, 0, 0, 100));
				target.draw(max_health_bar);

				sf::RectangleShape health_bar(sf::Vector2f(radius * 2.0f * ((float)health_ / max_health_), 8));
				health_bar.setPosition(screen_x - radius, screen_y + radius * 1.2f);
				health_bar.setFillColor(sf::Color(0, 255, 0, 100));
				target.draw(health_bar);
			}

			// render velocity line
			if (game.debug())
			{
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(screen_x, screen_y), sf::Color::Red),
					sf::Vertex(sf::Vector2f(
						game.OnScreenX(x_ + vel_x_),
						game.OnScreenY(y_ + vel_y_)
					), sf::Color::Red)
				};
				target.draw(line, 2, sf::Lines);
			}
		}
	}
}
