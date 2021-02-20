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
                if (CanGet(obj))
                {
                    health_ = 0;
                    OnGet(obj);
                    obj->Push(cos(dir), sin(dir));
                }
                else
                {
                    Push(cos(dir), sin(dir));
                }
            }

            virtual void OnGet(Object* obj) = 0;
            virtual bool CanGet(Object* obj)
            {
                return obj->type() == Type::kTank;
            }
        };
    }
}
