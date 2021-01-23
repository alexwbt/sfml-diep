#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <list>
#include <algorithm>

namespace diep
{
	namespace object
	{
		class Object;
	};

	struct GameData
	{
		virtual void SetData(sf::Packet& data) = 0;
		virtual void GetData(sf::Packet& data) = 0;
	};

	class Game : public GameData
	{
	private:
		float grid_size_ = 50.0f;
		float grid_line_width_ = 0.5f;

		float cam_x_ = 0.0f, cam_y_ = 0.0f;
		float scale_ = 3.0f;
		uint32_t win_width_ = 0, win_height_ = 0;

		uint64_t focus_id_ = 0;
		uint64_t control_id_ = 0;

		uint64_t next_id_ = 1;
		std::list<object::Object*> objects_;
		std::list<object::Object*> spawn_list_;
		std::list<object::Object*> particles_;

		bool debug_ = false;

	public:
		~Game();

		void SetData(sf::Packet& data) override;
		void GetData(sf::Packet& data) override;

		void Update(sf::Window& window);
		void Render(sf::RenderTarget& target) const;

		void KeyPressed(int key);

		float Scale() const { return scale_; }
		void Scale(float scale) { scale_ = scale < 1 ? 1 : scale; }
		const std::list<object::Object*>& Objects() const { return objects_; }

		void SetFocus(uint64_t id) { focus_id_ = id; }
		void SetControl(uint64_t id) { control_id_ = id; }

		void SetWindowSize(const sf::Vector2u& size);

		void Spawn(object::Object* obj);
		uint64_t NextId() { return next_id_++; };

		float Game::OnScreenX(float game_x) const { return (game_x - cam_x_) * scale_ + win_width_ / 2.0f; }
		float Game::OnScreenY(float game_y) const { return (game_y - cam_y_) * scale_ + win_height_ / 2.0f; }

		bool debug() const { return debug_; }
	};
}

#include "util/math.h"

#include "weapon/component.h"
#include "weapon/weapon.h"
#include "weapon/cannon.h"

#include "object/object.h"
#include "object/tank.h"
#include "object/projectile.h"

#include "util/collision.h"
