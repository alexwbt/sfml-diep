#pragma once

namespace diep
{
    namespace object
    {
        class Projectile : public Object
        {
        private:
            int lifetime_;

        public:
            Projectile(
                Game& game,
                uint64_t id,
                uint64_t team,
                float x,
                float y,
                float radius,
                float vel_x,
                float vel_y,
                int lifetime
            );

            void Update() override;
        };
    }
}
