#pragma once
#include "object.h"

namespace diep
{
    namespace object
    {
        class Projectile : public Object
        {
        private:
            int lifetime_;

        public:
            Projectile(unsigned int id, float x, float y, float radius, float vel_x, float vel_y, float lifetime);

            void Update() override;
        };
    }
}
