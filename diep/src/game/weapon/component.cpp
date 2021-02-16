#include "../game.h"

namespace diep
{
    namespace weapon
    {
        void Component::Update()
        {
            if (!weapon_.firing() && delay_ > 0 && reload_timer_ < 0)
            {
                reload_timer_++;
            }
            if (reload_timer_ > 0 || (weapon_.firing() && reload_timer_ > -delay_ * weapon_.reload_speed() * reload_speed_mod_))
            {
                reload_timer_--;
            }
            else if (weapon_.firing())
            {
                Fire();
                reload_timer_ = (weapon_.reload_speed() - delay_ * weapon_.reload_speed()) * reload_speed_mod_;
            }
        }

        void Component::Render(sf::RenderTarget& target) const
        {
            const float dir = dir_ + dir_offset_;
            const float reload_percent = 1 - reload_timer_ / (weapon_.reload_speed() * reload_speed_mod_);
            const float length = length_ * (1 - recoil_percent_ + reload_percent * recoil_percent_);

            sf::Vector2f vertices[4] = {
                sf::Vector2f(x_offset_, y_offset_ - width_ / 2),
                sf::Vector2f(x_offset_ + length, y_offset_ - width_ / 2),
                sf::Vector2f(x_offset_ + length, y_offset_ + width_ / 2),
                sf::Vector2f(x_offset_, y_offset_ + width_ / 2)
            };

            sf::ConvexShape shape(4);

            shape.setFillColor(sf::Color(150, 150, 150, 255));
            shape.setOutlineColor(sf::Color(100, 100, 100, 255));
            shape.setOutlineThickness(weapon_.owner()->game.Scale());
            for (int i = 0; i < 4; i++) {
                const float rad = atan2(vertices[i].y, vertices[i].x) + dir;
                const float mag = sqrt(pow(vertices[i].x, 2) + pow(vertices[i].y, 2));
                shape.setPoint(i, sf::Vector2f(
                    weapon_.owner()->game.OnScreenX(weapon_.owner()->x() + cos(rad) * weapon_.owner()->radius() * mag),
                    weapon_.owner()->game.OnScreenY(weapon_.owner()->y() + sin(rad) * weapon_.owner()->radius() * mag)
                ));
            }
            target.draw(shape);
        }
    }
}
