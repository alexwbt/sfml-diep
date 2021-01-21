#pragma once

#include <list>
#include <SFML/Graphics.hpp>

#include "object\tank.h"

namespace diep
{
	class Game
	{
	public:
		static Game& Instance()
		{
			static Game instance;
			return instance;
		}

	private:
		float grid_size_ = 50.0f;
		float grid_line_width_ = 0.5f;

		float cam_x_ = 0.0f, cam_y_ = 0.0f;
		float scale_ = 3.0f;
		float win_width_ = 0.0f, win_height_ = 0.0f;

		uint64_t focus_id_ = 0;
		uint64_t control_id_ = 0;

		std::list<object::Object*> objects_;
		std::list<object::Object*> spawn_list_;

		bool debug_ = false;

	private:
		Game()
		{
			objects_.push_back(new object::Tank(0, 0, 0, 10));
			bool ctrls[object::Tank::kControlListSize] = { false, true, false, false, false };
			object::Tank* tank = new object::Tank(NextId(), 300, 0, 30);
			tank->SetControls(ctrls);
			objects_.push_back(tank);
		}

		~Game();

	public:
		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

		float Scale() const { return scale_; }
		void Scale(float scale) { scale_ = scale < 1 ? 1 : scale; }
		const std::list<object::Object*>& Objects() const { return objects_; }

		void Update(sf::RenderWindow& window);
		void Render(sf::RenderWindow& window) const;

		void SetWindowSize(const sf::Vector2u& size);

		float Game::OnScreenX(float game_x) const { return (game_x - cam_x_) * scale_ + win_width_ / 2.0f; }
		float Game::OnScreenY(float game_y) const { return (game_y - cam_y_) * scale_ + win_height_ / 2.0f; }

		void Spawn(object::Object* obj);
		uint64_t NextId() const { static uint64_t next_id = 1; return next_id++; };

		void KeyPressed(int key);

		bool debug() const { return debug_; }
	};
}
