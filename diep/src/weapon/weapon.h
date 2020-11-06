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

			WeaponData* data;

		public:
			Weapon::Weapon(const object::Object* owner, Type type);
			~Weapon();

			void Fire(bool fire) { data->firing = fire; }
			void Turn(float dir);

			void Update();
			void Render(sf::RenderWindow& window) const;
		};
	}
}
