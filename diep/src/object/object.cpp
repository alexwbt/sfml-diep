#include "object.h"
#include "../game.h"
#include "../util/collision.h"

namespace diep
{
	namespace object
	{
		constexpr float Object::kVelocityStep = 0.05f;

		void Object::Push(float x, float y)
		{
			vel_x_ += x;
			vel_y_ += y;
		}

		void Object::Update()
		{
			const Game& game = Game::Instance();

			float vel_dir = atan2(vel_y_, vel_x_);
			float vel = sqrt(vel_x_ * vel_x_ + vel_y_ * vel_y_);
			while (vel >= kVelocityStep)
			{
				x_ += vel_x_ * kVelocityStep;
				y_ += vel_y_ * kVelocityStep;
				vel -= kVelocityStep;
				for (Object* obj : game.Objects())
				{
					if (obj->id_ != id_ && coll::collide(*this, *obj))
					{
						//float force = mass_ * vel / 10.0f; // ?
						float dir = atan2(obj->y_ - y_, obj->x_ - x_);
						float fx = cos(dir);
						float fy = sin(dir);
						obj->Push(fx, fy);
						// Push(-fx, -fy);
						x_ -= fx * kVelocityStep;
						y_ -= fy * kVelocityStep;
						vel = 0;
						break;
					}
				}
			}
		}

		bool Object::OnScreen() const
		{
			// TODO: proper on screen function
			return true;
		}

		void Object::Render(sf::RenderWindow& window) const
		{
			const Game& game = Game::Instance();
			float radius = radius_ * game.Scale();
			float screen_x = game.OnScreenX(x_);
			float screen_y = game.OnScreenY(y_);

			sf::CircleShape circle(radius, 100);
			circle.setPosition(sf::Vector2f(screen_x - radius, screen_y - radius));
			circle.setFillColor(border_color_);
			window.draw(circle);
			radius -= game.Scale();
			circle.setRadius(radius);
			circle.setPosition(sf::Vector2f(screen_x - radius, screen_y - radius));
			circle.setFillColor(color_);
			window.draw(circle);

			// draw velocity line
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(screen_x, screen_y), sf::Color::Red),
				sf::Vertex(sf::Vector2f(
					game.OnScreenX(x_ + vel_x_),
					game.OnScreenY(y_ + vel_y_)
				), sf::Color::Red)
			};
			window.draw(line, 2, sf::Lines);
		}
	}
}
