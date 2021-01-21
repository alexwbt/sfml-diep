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
            const float x = (x_offset_ + length_) * data_->owner->radius();
            const float y = y_offset_ * data_->owner->radius();
            const float dir = dir_ + dir_offset_;
            const float mag = sqrt(x * x + y * y);
            const float radius = data_->owner->radius() * width_ / 2.0f;
            object::Projectile* ball = new object::Projectile(
                game.NextId(),
                data_->owner->x() + cos(dir) * mag,
                data_->owner->y() + sin(dir) * mag,
                radius,
                cos(dir),
                sin(dir),
                100
            );
            game.Spawn(ball);
        }
    }
}
