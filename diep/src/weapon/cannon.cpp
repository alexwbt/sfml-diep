#include "cannon.h"
#include "../game.h"
#include "../object/projectile.h"

namespace diep
{
    namespace weapon
    {
        void Cannon::Fire()
        {
            Game& game = Game::Instance();
            const float x = (x_offset_ + length_) * stat_->owner->radius();
            const float y = y_offset_ * stat_->owner->radius();
            const float dir = dir_ + dir_offset_;
            const float mag = sqrt(x * x + y * y);
            const float radius = stat_->owner->radius() * width_ / 2.0f;
            auto ball = new object::Projectile(
                game.NextId(),
                stat_->owner->team(),
                stat_->owner->x() + cos(dir) * mag,
                stat_->owner->y() + sin(dir) * mag,
                radius,
                cos(dir) * stat_->bullet_speed,
                sin(dir) * stat_->bullet_speed,
                stat_->bullet_lifetime
            );
            game.Spawn(ball);
        }
    }
}
