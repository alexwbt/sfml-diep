#include "cannon.h"
#include "../game.h"

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
            object::Object* ball = new object::Object(
                game.NextId(),
                data_->owner->X() + cos(dir) * mag,
                data_->owner->Y() + sin(dir) * mag,
                radius
            );
            ball->Dying(100);
            ball->Frictionless();
            ball->Push(sf::Vector2f(
                cos(data_->owner->velocity_dir()) * data_->owner->velocity() * ball->mass(),
                sin(data_->owner->velocity_dir()) * data_->owner->velocity() * ball->mass()
            ));
            ball->Push(sf::Vector2f(cos(dir) * ball->mass(), sin(dir) * ball->mass()));
            game.Spawn(ball);
        }
    }
}
