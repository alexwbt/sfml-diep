#include "../game.h"

namespace diep
{
    namespace weapon
    {
        void Cannon::Fire()
        {
            float x = (x_offset_ + length_) * weapon_.owner()->radius();
            float y = y_offset_ * weapon_.owner()->radius();
            float dir = dir_ + dir_offset_;
            float mag = sqrt(x * x + y * y);
            float radius = weapon_.owner()->radius() * width_ / 2.0f;
            float vel_x = cos(dir)* weapon_.bullet_speed();
            float vel_y = sin(dir)* weapon_.bullet_speed();
            auto ball = new object::Projectile(
                weapon_.owner()->game,
                weapon_.owner()->game.NextId(),
                weapon_.owner()->team(),
                weapon_.owner()->x() + cos(dir + atan2(y, x)) * mag,
                weapon_.owner()->y() + sin(dir + atan2(y, x)) * mag,
                radius,
                vel_x,// + weapon_.owner()->vel_x(),
                vel_y,// + weapon_.owner()->vel_y(),
                weapon_.bullet_lifetime()
            );
            weapon_.owner()->game.Spawn(ball);
            weapon_.owner()->Push(-vel_x / 2.0f, -vel_y / 2.0f);
        }
    }
}
