#pragma once

namespace diep
{
    namespace object
    {
        class Item : public Object
        {
        protected:
            void Collide(Object* obj) override
            {
                if (obj->type() == Type::kTank)
                {
                    should_remove_ = true;
                    OnCollide((Tank*)obj);
                }
                else
                {
                    float dir = atan2(y_ - obj->y(), x_ - obj->x());
                    Push(cos(dir), sin(dir));
                }
            }

            virtual void OnCollide(Tank* obj) = 0;
        };
    }
}
