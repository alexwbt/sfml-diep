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
		float grid_size_ = 20.0f;
		float grid_line_width_ = 0.5f;

		float cam_x_ = 0.0f, cam_y_ = 0.0f;
		float scale_ = 3.0f;
		unsigned int win_width_ = 0, win_height_ = 0;

		unsigned int focus_id_ = 0;
		unsigned int control_id_ = 0;

		std::list<object::Object*> objects_;

	private:
		Game()
		{
			objects_.push_back(new object::Tank(0, 0, 0, 10));
			bool ctrls[4] = { false, true, false, false };
			object::Tank* tank = new object::Tank(1, 300, 0, 30);
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
	};
}
