#pragma once

namespace diep
{
    namespace object
    {
        class Projectile : public Object
        {
        private:
            uint32_t lifetime_;

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
                uint32_t lifetime,
                uint32_t damage
            );

            void Update() override;

            // data
            void SetData(sf::Packet& data) override;
            void GetData(sf::Packet& data) override;
        };
    }
}
