#pragma once

namespace diep
{
    namespace object
    {
        class WeaponBall : public Item
        {
        private:
            weapon::Type weapon_type_;

            Tank display_;

        public:
            WeaponBall(Game& game, uint64_t id, float x, float y)
                : Item(game, id, x, y, 10), weapon_type_((weapon::Type)(rand() % (int)weapon::Type::End)),
                display_(game, 0, x, y, 4)
            {
                color_ = sf::Color::White;
                border_color_ = sf::Color(200, 200, 200);

                display_.SetBorderDiff(0.3f);
                display_.SetColor(sf::Color::White, sf::Color(100, 100, 100));
                display_.SetWeapon(weapon_type_);
            }

            void Update()
            {
                Item::Update();
                display_.SetPos(x_ - 1.5f, y_);
            }

            void Render(sf::RenderTarget& target) const override
            {
                Item::Render(target);
                display_.Render(target);
            }

        protected:
            void OnGet(Tank* obj) override
            {
                obj->SetWeapon(weapon_type_);
            }
        };
    }
}
