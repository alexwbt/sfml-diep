#pragma once

namespace diep
{
	namespace object
	{
		class Tank : public Object
		{
		public:
			static constexpr int kControlListSize = 5;

		private:
			bool controls_[kControlListSize] = { 0, 0, 0, 0, 0 };

			float move_force_ = 0.1f;

			weapon::Weapon* weapon_;

		public:
			Tank(Game& game, uint64_t id, float x, float y, float radius)
				: Object(game, id, x, y, radius), weapon_(new weapon::Weapon(this, weapon::Type::kTwinCannon))
			{
				type_ = Type::kTank;
			}

			~Tank();

			void SetWeapon(weapon::Type type);

			void SetControls(bool* controls);
			void Turn(float dir) { weapon_->Turn(dir); }

			void Update() override;
			void Render(sf::RenderTarget& target) const override;
		};
	}
}
