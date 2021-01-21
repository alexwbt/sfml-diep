#pragma once

#include <SFML/Graphics.hpp>

#include <list>

namespace diep
{
	namespace object
	{
		enum class Shape
		{
			kCircle = 0b1
		};

		enum class Type
		{
			kObject,
			kTank
		};

		class Object
		{
		public:
			static const float kFrictionForce;
			static const float kVelocityStep;

		protected:
			unsigned int id_;
			float x_, y_;
			float radius_;

			float vel_ = 0.0f;
			float vel_dir_ = 0.0f;
			float mass_;
			bool frictionless_ = false;
			bool should_remove_ = false;

			Shape shape_ = Shape::kCircle;
			Type type_ = Type::kObject;
			sf::Color color_ = sf::Color(0, 170, 255, 255);
			sf::Color border_color_ = sf::Color(0, 100, 200, 255);

			std::list<sf::Vector2f> forces_;

			bool dying_ = false;
			int dying_timer_ = 0;

		public:
			Object(unsigned int id, float x, float y, float radius)
				: id_(id), x_(x), y_(y), radius_(radius)
			{
				mass_ = 3.14159f * pow(radius, 2);
			}

			unsigned int id() const { return id_; }
			float X() const { return x_; }
			float Y() const { return y_; }
			float radius() const { return radius_; }
			float mass() const { return mass_; }
			Type type() const { return type_; }
			Shape shape() const { return shape_; }
			bool should_remove() const { return should_remove_; }
			float velocity() const { return vel_; }
			float velocity_dir() const { return vel_dir_; }

			void Frictionless() { frictionless_ = true; }
			void Push(const sf::Vector2f force) { forces_.push_back(force); }
			void Dying(int time) { dying_ = true; dying_timer_ = time; }

			virtual bool OnScreen() const;

			virtual void Update();
			virtual void Render(sf::RenderWindow& window) const;
		};
	}
}
