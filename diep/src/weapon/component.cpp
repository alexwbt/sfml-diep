#include "component.h"
#include "../game.h"

namespace diep
{
	namespace weapon
	{
		void Component::Update()
		{
			if (reload_timer_ > 0 || (data_->firing && reload_timer_ > -delay_ * reload_speed_mod_))
			{
				reload_timer_--;
			}
			else if (data_->firing)
			{
				Fire();
				reload_timer_ = (data_->reload_speed - delay_) * reload_speed_mod_;
			}
		}

		void Component::Render(sf::RenderWindow& window) const
		{
			const float dir = dir_ + dir_offset_;
			const float reload_percent = 1 - reload_timer_ / (data_->reload_speed * reload_speed_mod_);
			const float length = length_;// *(1 - recoil_percent_ + reload_percent * recoil_percent_);

			sf::Vector2f vertices[4] = {
				sf::Vector2f(x_offset_, y_offset_ - width_ / 2),
				sf::Vector2f(x_offset_ + length, y_offset_ - width_ / 2),
				sf::Vector2f(x_offset_ + length, y_offset_ + width_ / 2),
				sf::Vector2f(x_offset_, y_offset_ + width_ / 2)
			};

			const Game& game = Game::Instance();
			sf::ConvexShape shape(4);
			shape.setFillColor(sf::Color(150, 150, 150, 255));
			shape.setOutlineColor(sf::Color(100, 100, 100, 255));
			shape.setOutlineThickness(game.Scale());
			for (int i = 0; i < 4; i++) {
				const float rad = atan2(vertices[i].y, vertices[i].x) + dir;
				const float mag = sqrt(pow(vertices[i].x, 2) + pow(vertices[i].y, 2));
				shape.setPoint(i, sf::Vector2f(
					game.OnScreenX(data_->owner->X() + cos(rad) * data_->owner->Radius() * mag),
					game.OnScreenY(data_->owner->Y() + sin(rad) * data_->owner->Radius() * mag)
				));
			}
			window.draw(shape);
		}
	}
}
