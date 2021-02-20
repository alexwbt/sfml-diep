#pragma once

namespace diep
{
    namespace object
    {
        class HeavyProjectile : public Projectile
        {
        public:
            HeavyProjectile( Game& game, uint64_t id, uint64_t team,
                float x, float y, float radius, float vel_x, float vel_y, uint32_t lifetime, uint32_t damage)
                : Projectile( game, id, team, x, y, radius, vel_x, vel_y, lifetime, damage)
            {
                push_back_mod_ = 1.0f;
            }

            void Collide(Object* obj) override
            {}
        };
    }
}
