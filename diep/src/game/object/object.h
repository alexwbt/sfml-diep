#pragma once

namespace diep
{
	namespace object
	{
		enum class Shape
		{
			kCircle = 0b1,
			kPolygon = 0b10
		};

		enum class Type
		{
			kObject,
			kTank,
			kProjectile
		};

		class Object : public GameData
		{
		public:
			Game& game;

		protected:
			// basic
			uint64_t id_;
			float x_, y_;
			float radius_;
			float rotate_;

			// physics
			float vel_x_, vel_y_;
			bool friction_ = true;

			// game
			Type type_;
			uint64_t team_;
			uint32_t health_, max_health_;
			uint32_t body_damage_;
			bool dead_ = false;

			// render
			uint8_t points_ = 100;
			uint8_t opacity_ = 255;
			Shape shape_ = Shape::kCircle;
			sf::Color color_ = sf::Color(0, 170, 255, 255);
			sf::Color border_color_ = sf::Color(0, 100, 200, 255);

			bool render_health_ = true;

		public:
			Object(Game& game, uint64_t id, float x, float y, float radius)
				: game(game), id_(id), type_(Type::kObject), team_(id), x_(x), y_(y), radius_(radius), vel_x_(0), vel_y_(0),
				rotate_(0), health_(100), max_health_(100), body_damage_(10)
			{}

			// polygon
			Object(Game& game, uint64_t id, float x, float y, float radius, uint8_t points)
				: game(game), id_(id), type_(Type::kObject), team_(id), x_(x), y_(y), radius_(radius), points_(points), vel_x_(0), vel_y_(0),
				rotate_(0), health_((int)radius * 2), max_health_((int)radius * 2), body_damage_(10), shape_(Shape::kPolygon)
			{}

			// data
			void SetData(sf::Packet& data) override;
			void GetData(sf::Packet& data) override;

			// getters
			uint64_t id() const { return id_; }
			float x() const { return x_; }
			float y() const { return y_; }
			float radius() const { return radius_; }
			float rotate() const { return rotate_; }
			float vel_x() const { return vel_x_; }
			float vel_y() const { return vel_y_; }
			uint64_t team() const { return team_; }
			bool dead() const { return dead_; }
			Type type() const { return type_; }
			Shape shape() const { return shape_; }
			uint8_t opacity() const { return opacity_; }
			uint8_t points() const { return points_; }

			// setter
			void SetColor(const sf::Color color, const sf::Color border_color);

			// physics
			void Push(float x, float y);

			// update
			virtual void Update();

			// render
			virtual bool OnScreen() const;
			virtual void Render(sf::RenderTarget& target) const;
		};
	}
}
