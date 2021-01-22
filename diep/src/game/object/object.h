#pragma once

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
			Game& game;

		protected:
			// basic
			uint64_t id_;
			float x_, y_;
			float radius_;

			// physics
			float vel_x_, vel_y_;

			// game
			uint64_t team_;
			int health_, max_health_;
			bool should_remove_ = false;

			// render
			Shape shape_ = Shape::kCircle;
			Type type_ = Type::kObject;
			sf::Color color_ = sf::Color(0, 170, 255, 255);
			sf::Color border_color_ = sf::Color(0, 100, 200, 255);

			bool render_health_ = true;

		public:
			Object(Game& game, uint64_t id, float x, float y, float radius)
				: game(game), id_(id), team_(id), x_(x), y_(y), radius_(radius), vel_x_(0), vel_y_(0),
				health_(100), max_health_(100)
			{}

			// getters
			uint64_t id() const { return id_; }
			float x() const { return x_; }
			float y() const { return y_; }
			float radius() const { return radius_; }
			float vel_x() const { return vel_x_; }
			float vel_y() const { return vel_y_; }
			uint64_t team() const { return team_; }
			bool should_remove() const { return should_remove_; }
			Type type() const { return type_; }
			Shape shape() const { return shape_; }

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
