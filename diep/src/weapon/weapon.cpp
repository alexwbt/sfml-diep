#include "weapon.h"
#include "cannon.h"

namespace diep
{
	namespace weapon
	{
		WeaponData* Weapon::CreateWeapon(const object::Object* owner, Weapon* weapon)
		{
			WeaponData* data = new WeaponData;
			data->owner = owner;

			switch (weapon->type_)
			{
			case Type::kSingleConnon:
				weapon->components_.push_back(new Cannon(data));
				break;
			}

			return data;
		}

		Weapon::~Weapon()
		{
			for (const Component* component : components_)
				delete component;

			delete data_;
		}

		void Weapon::Turn(float dir)
		{
			for (Component* component : components_)
				component->Turn(dir);
		}

		void Weapon::Update()
		{
			for (Component* component : components_)
				component->Update();
		}

		void Weapon::Render(sf::RenderWindow& window) const
		{
			for (Component* component : components_)
				component->Render(window);
		}
	}
}
