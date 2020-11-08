#include "cannon.h"
#include "../game.h"

namespace diep
{
    namespace weapon
    {
        void Cannon::Fire()
        {
            Game& game = Game::Instance();
            const float x = (x_offset_ + length_) * data_->owner->Radius();
            const float y = y_offset_ * data_->owner->Radius();
            const float dir = dir_ + dir_offset_;
            const float mag = sqrt(x * x + y * y);
            const float radius = data_->owner->Radius() * width_ / 2.0f;
            object::Object* ball = new object::Object(
                game.NextId(),
                data_->owner->X() + cos(dir) * mag,
                data_->owner->Y() + sin(dir) * mag,
                radius
            );
            ball->Frictionless();
            ball->Push(sf::Vector2f(
                cos(data_->owner->VelocityDir()) * data_->owner->Velocity() * ball->Mass(),
                sin(data_->owner->VelocityDir()) * data_->owner->Velocity() * ball->Mass()
            ));
            ball->Push(sf::Vector2f(cos(dir) * ball->Mass(), sin(dir) * ball->Mass()));
            game.Spawn(ball);
        }
    }
}
