#pragma once

namespace diep
{
    namespace object
    {
        class HealthBall : public Item
        {
        public:
            HealthBall(Game& game, uint64_t id, float x, float y)
                : Item(game, id, x, y, 10)
            {
                color_ = sf::Color(85, 221, 153);
                border_color_ = sf::Color(40, 100, 60);
            }

            void Render(sf::RenderTarget& target) const override
            {
                Item::Render(target);

                float radius = radius_ * game.Scale();
                float screen_x = game.OnScreenX(x_);
                float screen_y = game.OnScreenY(y_);
                auto size = sf::Vector2f(radius * 1.0f, radius * 0.3f);
                sf::RectangleShape rect(size);
                rect.setPosition(screen_x - size.x / 2.0f, screen_y - size.y / 2.0f);
                rect.setFillColor(sf::Color::White);
                target.draw(rect);

                rect.setSize(sf::Vector2f(size.y, size.x));
                rect.setPosition(screen_x - size.y / 2.0f, screen_y - size.x / 2.0f);
                target.draw(rect);
            }

        protected:
            void OnGet(Object* obj) override
            {
                obj->SetHealth(obj->health() + 20);
            }

            bool CanGet(Object* obj) override
            {
                return Item::CanGet(obj) && obj->health() < obj->max_health();
            }
        };
    }
}
