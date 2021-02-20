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

			~Tank()
			{
				delete weapon_;
			}

			void SetWeapon(weapon::Type type)
			{
				delete weapon_;
				weapon_ = new weapon::Weapon(this, type);
			}

			void SetControls(bool* controls)
			{
				for (int i = 0; i < object::Tank::kControlListSize; i++)
					controls_[i] = controls[i];
			}

			void Turn(float dir)
			{
				weapon_->Turn(dir);
			}

			void Update() override
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

			void Render(sf::RenderTarget& target) const override
			{
				weapon_->Render(target);
				Object::Render(target);
			}
		};
	}
}
