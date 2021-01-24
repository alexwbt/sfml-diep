#pragma once

namespace diep
{
	namespace weapon
	{
		enum class Type
		{
			kSingleConnon,
			kTwinCannon
		};

		class Weapon
		{
		private:
			Type type_;

			object::Object* owner_;
			bool firing_ = false;
			float reload_speed_ = 30.0f;
			float bullet_speed_ = 2.0f;
			uint32_t bullet_lifetime_ = 100;

			uint8_t component_count_;
			Component** components_;

		public:
			Weapon(object::Object* owner, Type type);
			~Weapon();

			// getter
			object::Object* owner() const { return owner_; }
			bool firing() const { return firing_; }
			float reload_speed() const { return reload_speed_; }
			float bullet_speed() const { return bullet_speed_; }
			uint32_t bullet_lifetime() const { return bullet_lifetime_; }

			void Fire(bool fire) { firing_ = fire; }
			void Turn(float dir);

			void Update();
			void Render(sf::RenderTarget& target) const;
		};
	}
}
