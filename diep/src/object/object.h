#pragma once

#include <SFML/Graphics.hpp>

#include <list>

#include "../util/math.h"

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
			// basic
			unsigned int id_;
			float x_, y_;
			float radius_;

			// physics
			float vel_x_, vel_y_;
			float mass_;

			// game
			bool should_remove_ = false;

			// render
			Shape shape_ = Shape::kCircle;
			Type type_ = Type::kObject;
			sf::Color color_ = sf::Color(0, 170, 255, 255);
			sf::Color border_color_ = sf::Color(0, 100, 200, 255);

		public:
			Object(unsigned int id, float x, float y, float radius)
				: id_(id), x_(x), y_(y), radius_(radius), vel_x_(0), vel_y_(0)
			{
				mass_ = math::PI * radius * radius;
			}

			// getters
			unsigned int id() const { return id_; }
			float x() const { return x_; }
			float y() const { return y_; }
			float radius() const { return radius_; }
			float vel_x() const { return vel_x_; }
			float vel_y() const { return vel_y_; }
			float mass() const { return mass_; }
			Type type() const { return type_; }
			Shape shape() const { return shape_; }
			bool should_remove() const { return should_remove_; }

			// physics
			void Push(float x, float y);

			// update
			virtual void Update();

			// render
			virtual bool OnScreen() const;
			virtual void Render(sf::RenderWindow& window) const;
		};
	}
}
