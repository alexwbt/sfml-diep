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
            int lifetime
        ) : Object(game, id, x, y, radius), lifetime_(lifetime)
        {
            team_ = team;
            vel_x_ = vel_x;
            vel_y_ = vel_y;
        }

        void Projectile::Update()
        {
            Object::Update();

            if (--lifetime_ <= 0)
                should_remove_ = true;
        }
    }
}
