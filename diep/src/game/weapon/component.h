#pragma once

namespace diep
{
	namespace weapon
	{
		class Component
		{
		protected:
			const WeaponStatus* stat_;

			float reload_timer_ = 0.0f;
			float reload_speed_mod_;
			float delay_;

			float x_offset_, y_offset_;
			float length_, width_;
			float recoil_percent_;

			float dir_ = 0.0f;
			float dir_offset_;

		public:
			Component(
				WeaponStatus* stat,
				float length = 1.5f,
				float width = 0.6f,
				float dir_offset = 0.0f,
				float x_offset = 0.0f,
				float y_offset = 0.0f,
				float reload_speed_mod = 1.0f,
				float delay = 0.0f,
				float recoil_percent = 0.1f
			) : stat_(stat),
				length_(length),
				width_(width),
				dir_offset_(dir_offset),
				x_offset_(x_offset),
				y_offset_(y_offset),
				reload_speed_mod_(reload_speed_mod),
				delay_(delay),
				recoil_percent_(recoil_percent) {}

			virtual void Fire() = 0;
			virtual void Turn(float dir) { dir_ = dir; }

			virtual void Update();
			virtual void Render(sf::RenderWindow& window) const;
		};
	}
}
