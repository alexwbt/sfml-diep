#pragma once

#include <list>

#include "component.h"

namespace diep
{
	namespace weapon
	{
		enum class Type
		{
			kSingleConnon
		};

		class Weapon
		{
		private:
			static WeaponData* Weapon::CreateWeapon(const object::Object* owner, Weapon* weapon);

		private:
			Type type_;

			std::list<Component*> components_;

			WeaponData* data_;

		public:
			Weapon::Weapon(const object::Object* owner, Type type)
				: type_(type), data_(CreateWeapon(owner, this)) {}
			~Weapon();

			void Fire(bool fire) { data_->firing = fire; }
			void Turn(float dir);

			void Update();
			void Render(sf::RenderWindow& window) const;
		};
	}
}
