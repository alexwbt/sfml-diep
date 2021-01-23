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
				components_ = new Component*[component_count_];
				components_[0] = new Cannon(*this);
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
