#include "../game.h"

namespace diep
{
    namespace weapon
    {
        Weapon::Weapon(object::Object* owner, Type type)
            : owner_(owner), type_(type), component_count_(0), components_(nullptr)
        {
            switch (type)
            {
            case Type::kSingleConnon:
                component_count_ = 1;
                components_ = new Component * [1];
                components_[0] = new Cannon<>(*this);
                break;
            case Type::kTwinCannon:
                component_count_ = 2;
                components_ = new Component * [2];
                components_[0] = new Cannon<>(*this, 1.5f, 0.6f, 0, 0, -0.5f);
                components_[1] = new Cannon<>(*this, 1.5f, 0.6f, 0, 0, 0.5f, 1.0f, 0.5f);
                break;
            case Type::kHeavyCannon:
                component_count_ = 1;
                components_ = new Component * [1];
                components_[0] = new Cannon<object::HeavyProjectile>(*this, 1.8f, 1.5f, 0.0f, 0.0f, 0.0f, 3.0f);
                break;
            }
        }

        Weapon::~Weapon()
        {
            for (int i = 0; i < component_count_; i++)
                delete components_[i];
        }

        void Weapon::Turn(float dir)
        {
            for (int i = 0; i < component_count_; i++)
                components_[i]->Turn(dir);
        }

        void Weapon::Update()
        {
            for (int i = 0; i < component_count_; i++)
                components_[i]->Update();
        }

        void Weapon::Render(sf::RenderTarget& target) const
        {
            for (int i = 0; i < component_count_; i++)
                components_[i]->Render(target);
        }
    }
}
