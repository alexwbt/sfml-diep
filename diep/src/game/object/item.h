#pragma once

namespace diep
{
    namespace object
    {
        class Item : public Object
        {
        public:
            Item(Game& game, uint64_t id, float x, float y, float radius)
                : Object(game, id, x, y, radius)
            {
                body_damage_ = 0;
                render_health_ = false;
            }

        protected:
            void Collide(Object* obj) override
            {
                float dir = atan2(y_ - obj->y(), x_ - obj->x());
                if (obj->type() == Type::kTank)
                {
                    health_ = 0;
                    OnGet((Tank*)obj);
                    obj->Push(cos(dir), sin(dir));
                }
                else
                {
                    Push(cos(dir), sin(dir));
                }
            }

            virtual void OnGet(Tank* obj) = 0;
        };
    }
}
