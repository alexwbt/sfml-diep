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

			Shape shape_ = Shape::kCircle;
			Type type_ = Type::kObject;
			sf::Color color_ = sf::Color(0, 170, 255, 255);
			sf::Color border_color_ = sf::Color(0, 100, 200, 255);

			std::list<sf::Vector2f> forces_;

		public:
			Object(unsigned int id, float x, float y, float radius)
				: id_(id), x_(x), y_(y), radius_(radius)
			{
				mass_ = 3.14159f * pow(radius, 2);
			}

			unsigned int Id() const { return id_; }
			float X() const { return x_; }
			float Y() const { return y_; }
			float Radius() const { return radius_; }
			Type Type() const { return type_; }
			Shape Shape() const { return shape_; }

			void Push(const sf::Vector2f& force) { forces_.push_back(force); }

			virtual bool OnScreen() const;

			virtual void Update();
			virtual void Render(sf::RenderWindow& window) const;
		};
	}
}
