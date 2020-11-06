#include "tank.h"

namespace diep
{
	namespace object
	{
		void Tank::SetControls(bool* controls)
		{
			for (int i = 0; i < 4; i++)
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
				forces_.push_back({
					cos(move_dir) * move_force_,
					sin(move_dir) * move_force_
				});
			}

			Object::Update();
			weapon_.Update();
		}

		void Tank::Render(sf::RenderWindow& window) const
		{
			weapon_.Render(window);
			Object::Render(window);
		}
	}
}
