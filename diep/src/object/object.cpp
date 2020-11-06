#include "object.h"
#include "../game.h"
#include "../collision.h"

namespace diep
{
	namespace object
	{
		const float Object::kFrictionForce = 1.0f;
		const float Object::kVelocityStep = 0.05f;

		bool Object::OnScreen() const
		{
			return true;
		}

		void Object::Update()
		{
			float force_x = 0.0f;
			float force_y = 0.0f;
			for (const sf::Vector2f& force : forces_)
			{
				force_x += force.x;
				force_y += force.y;
			}
			forces_.clear();

			float x_vel = cos(vel_dir_) * vel_;
			float y_vel = sin(vel_dir_) * vel_;
			float friction_x = abs(x_vel) < kFrictionForce ? -x_vel : kFrictionForce * (-x_vel / abs(x_vel));
			float friction_y = abs(y_vel) < kFrictionForce ? -y_vel : kFrictionForce * (-y_vel / abs(y_vel));
			float accel_x = (force_x + friction_x) / mass_;
			float accel_y = (force_y + friction_y) / mass_;
			x_vel += accel_x;
			y_vel += accel_y;
			vel_ = sqrt(pow(x_vel, 2) + pow(y_vel, 2));
			vel_dir_ = atan2(y_vel, x_vel);
			if (vel_ < 0.0001f) vel_ = 0.0f;

			const Game& game = Game::Instance();
			float vel = vel_;
			while (vel >= kVelocityStep)
			{
				x_ += cos(vel_dir_) * kVelocityStep;
				y_ += sin(vel_dir_) * kVelocityStep;
				vel -= kVelocityStep;
				for (Object* obj : game.Objects())
				{
					if (obj->id_ != id_ && coll::collide(*this, *obj))
					{
						float force = mass_ * pow(vel_, 2);
						float dir = atan2(obj->y_ - y_, obj->x_ - x_);
						float fx = cos(dir);
						float fy = sin(dir);
						obj->forces_.push_back(sf::Vector2f(fx * force, fy * force));
						forces_.push_back(sf::Vector2f(-fx * force, -fy * force));
						x_ -= fx * kVelocityStep;
						y_ -= fy * kVelocityStep;
						vel = 0;
						break;
					}
				}
			}
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
					game.OnScreenX(x_ + cos(vel_dir_) * vel_ * 10.0f),
					game.OnScreenY(y_ + sin(vel_dir_) * vel_ * 10.0f)
				), sf::Color::Red)
			};
			window.draw(line, 2, sf::Lines);
		}
	}
}
