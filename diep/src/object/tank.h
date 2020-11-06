#pragma once

#include "object.h"
#include "../weapon/weapon.h"

namespace diep
{
	namespace object
	{
		class Tank : public Object
		{
		private:
			bool controls_[4];

			float move_force_ = 2.0f;

			weapon::Weapon weapon_;

		public:
			Tank(unsigned int id, float x, float y, float radius)
				: Object(id, x, y, radius), weapon_(this, weapon::Type::kSingleConnon)
			{
				type_ = Type::kTank;
			}

			void SetControls(bool* controls);
			void Turn(float dir) { weapon_.Turn(dir); }

			void Update() override;
			void Render(sf::RenderWindow& window) const override;
		};
	}
}
