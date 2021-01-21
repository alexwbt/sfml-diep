#include "projectile.h"

namespace diep
{
    namespace object
    {
        Projectile::Projectile(unsigned int id, float x, float y, float radius, float vel_x, float vel_y, float lifetime)
            : Object(id, x, y, radius), lifetime_(lifetime)
        {
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
