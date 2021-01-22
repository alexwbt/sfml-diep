#pragma once

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
			static WeaponStatus* Weapon::CreateWeapon(const object::Object* owner, Weapon* weapon);

		private:
			Type type_;

			std::list<Component*> components_;

			WeaponStatus* stat_;

		public:
			Weapon::Weapon(const object::Object* owner, Type type)
				: type_(type), stat_(CreateWeapon(owner, this)) {}
			~Weapon();

			void Fire(bool fire) { stat_->firing = fire; }
			void Turn(float dir);

			void Update();
			void Render(sf::RenderTarget& target) const;
		};
	}
}
