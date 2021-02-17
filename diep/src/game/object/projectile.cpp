#include "../game.h"

namespace diep
{
    namespace object
    {
        Projectile::Projectile(
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

        void Projectile::Update()
        {
            Object::Update();

            if (!is_particle_)
            {
                lifetime_ = std::max((int)(lifetime_ - 1), 0);
                should_remove_ = lifetime_ == 0;
            }
        }

        void Projectile::SetData(sf::Packet& data)
        {
            Object::SetData(data);
            data >> lifetime_;
        }

        void Projectile::GetData(sf::Packet& data)
        {
            Object::GetData(data);
            data << lifetime_;
        }
    }
}
