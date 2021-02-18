#include "../game.h"

namespace diep
{
	namespace object
	{
		Tank::~Tank()
		{
			delete weapon_;
		}

		void Tank::SetWeapon(weapon::Type type)
		{
			delete weapon_;
			weapon_ = new weapon::Weapon(this, type);
		}

		void Tank::SetControls(bool* controls)
		{
			for (int i = 0; i < object::Tank::kControlListSize; i++)
				controls_[i] = controls[i];
		}

		void Tank::Update()
		{
			float input_x = 0.0f;
			float input_y = 0.0f;
			if (controls_[0]) input_y--;
			if (controls_[1]) input_x--;
			if (controls_[2]) input_y++;
			if (controls_[3]) input_x++;

			if (input_x != 0 || input_y != 0)
			{
				float move_dir = atan2(input_y, input_x);
				Push(cos(move_dir) * move_force_, sin(move_dir) * move_force_);
			}

			weapon_->Fire(controls_[4]);

			Object::Update();
			weapon_->Update();
		}

		void Tank::Render(sf::RenderTarget& target) const
		{
			weapon_->Render(target);
			Object::Render(target);
		}
	}
}
