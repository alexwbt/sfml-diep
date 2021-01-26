#include "../game.h"

namespace diep
{
	namespace object
	{
		void Object::SetData(sf::Packet& data)
		{
			
		}

		void Object::GetData(sf::Packet& data)
		{

		}

		void Object::SetColor(const sf::Color color, const sf::Color border_color)
		{
			color_ = color;
			border_color_ = border_color;
		}

		void Object::Push(float x, float y)
		{
			vel_x_ += x;
			vel_y_ += y;
		}

		void Object::Update()
		{
			x_ += vel_x_;
			y_ += vel_y_;

			if (friction_)
			{
				vel_x_ *= 0.95f;
				vel_y_ *= 0.95f;
				if (abs(vel_x_) < 0.01f) vel_x_ = 0;
				if (abs(vel_y_) < 0.01f) vel_y_ = 0;
			}

			if (dead_)
			{
				opacity_ = std::max(opacity_ - 10, 0);
				return;
			}

			for (Object* obj : game.Objects())
			{
				if (obj->id_ != id_ &&
					obj->team_ != team_ &&
					coll::collide(*this, *obj))
				{
					//health_ -= obj->body_damage_;
					opacity_ = 150;
					float dir = atan2(y_ - obj->y_, x_ - obj->x_);
					Push(cos(dir), sin(dir));
					break;
				}
			}

			if (health_ <= 0)
				dead_ = true;
			else opacity_ = std::min(opacity_ + 10, 255);
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

			sf::CircleShape border(radius, points_);
			border.setPosition(sf::Vector2f(screen_x, screen_y));
			border.setFillColor(border_color_);
			border.setOrigin(radius, radius);
			border.setRotation(rotate_);
			target.draw(border);

			float body_radius = radius - border_diff_ * game.Scale();
			sf::CircleShape body(body_radius, points_);
			body.setPosition(sf::Vector2f(screen_x, screen_y));
			body.setOrigin(body_radius, body_radius);
			body.setRotation(rotate_);
			body.setFillColor(color_);
			target.draw(body);

			// render health
			if (render_health_ && health_ < max_health_ && !dead_)
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

			if (game.debug())
			{
				// render velocity line
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(screen_x, screen_y), sf::Color::Red),
					sf::Vertex(sf::Vector2f(
						game.OnScreenX(x_ + vel_x_),
						game.OnScreenY(y_ + vel_y_)
					), sf::Color::Red)
				};
				target.draw(line, 2, sf::Lines);

				// render hitbox
				auto points = coll::polygon_get_points(x_, y_, radius_, points_, rotate_);
				sf::ConvexShape shape;
				shape.setFillColor(sf::Color(255, 0, 0, 100));
				shape.setPointCount(points_);
				for (int i = 0; i < points->size(); i++)
					shape.setPoint(i, sf::Vector2f(game.OnScreenX(points->at(i).x), game.OnScreenY(points->at(i).y)));
				target.draw(shape);
			}
		}
	}
}
