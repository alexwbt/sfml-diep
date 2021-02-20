#pragma once

namespace diep
{
    namespace object
    {
        class Projectile : public Object
        {
        private:
            uint32_t lifetime_;

        protected:
            float push_back_mod_ = 0.5f;

        public:
            Projectile(
                Game& game,
                uint64_t id,
                uint64_t team,
                float x,
                float y,
                float radius,
                float vel_x,
                float vel_y,
                uint32_t lifetime,
                uint32_t damage
            ) : Object(game, id, x, y, radius), lifetime_(lifetime)
            {
                team_ = team;
                vel_x_ = vel_x;
                vel_y_ = vel_y;
                friction_ = 0;
                render_health_ = false;
                body_damage_ = damage;
                type_ = Type::kProjectile;
            }

            float push_back_mod() const { return push_back_mod_; }

            void Update() override
            {
                Object::Update();

                if (!is_particle_)
                {
                    lifetime_ = std::max((int)(lifetime_ - 1), 0);
                    should_remove_ = lifetime_ == 0;
                }
            }

            void SetData(sf::Packet& data) override
            {
                Object::SetData(data);
                data >> lifetime_;
            }

            void GetData(sf::Packet& data) override
            {
                Object::GetData(data);
                data << lifetime_;
            }
        };
    }
}
