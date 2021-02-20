#include "game.h"

namespace diep
{
    Game::Game()
    {
        alpha_shader_.loadFromFile("src/shaders/alpha_shader.frag", sf::Shader::Fragment);
    }

    Game::~Game()
    {
        for (auto object : objects_)
            delete object;
        for (auto object : spawn_list_)
            delete object;
        for (auto object : particles_)
            delete object;
    }

    void Game::SetData(sf::Packet& data)
    {

    }

    void Game::GetData(sf::Packet& data)
    {
        for (auto object : objects_)
            object->GetData(data);
        for (auto object : particles_)
            object->GetData(data);
    }

    void Game::Update(sf::Window& window)
    {
        std::vector<object::Object*> objs;
        objs.reserve(objects_.size());
        objs.insert(objs.begin(), objects_.begin(), objects_.end());
        int size = (int)objs.size();
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = i + 1; j < objs.size(); j++)
            {
                if (objs[i]->id() != objs[j]->id() && coll::collide(*objs[i], *objs[j]))
                {
                    objs[i]->Collide(objs[j]);
                    objs[j]->Collide(objs[i]);
                    break;
                }
            }
        }

        particles_.remove_if([](object::Object* object)
            {
                object->Update();
                if (object->should_remove())
                {
                    delete object;
                    return true;
                }
                return false;
            });

        objects_.splice(objects_.begin(), spawn_list_);
        spawn_list_.clear();
        objects_.remove_if([this, &window](object::Object* object)
            {
                if (control_id_ == object->id() && object->type() == object::Type::kTank)
                {
                    object::Tank* tank = (object::Tank*)object;
                    bool controls[object::Tank::kControlListSize] =
                    {
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W),
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A),
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S),
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D),
                        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
                    };
                    tank->SetControls(controls);

                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    float dir = atan2f(mouse.y - win_height_ / 2.0f, mouse.x - win_width_ / 2.0f);
                    tank->Turn(dir);
                }
                object->Update();
                if (focus_id_ == object->id())
                {
                    cam_x_ = object->x();
                    cam_y_ = object->y();
                }

                if (object->should_remove())
                {
                    object->SetIsParticle(true);
                    object->SetShouldRemove(false);
                    particles_.push_back(object);
                    return true;
                }
                return false;
            });
    }

    void Game::Render(sf::RenderTarget& target)
    {
        const float grid_size = grid_size_ * scale_;
        const float grid_line_width = grid_line_width_ * scale_;

        for (float x = fmod(OnScreenX(0), grid_size); x < win_width_; x += grid_size)
        {
            sf::RectangleShape line(sf::Vector2f(grid_line_width, (float)win_height_));
            line.setPosition(x, -grid_line_width / 2.0f);
            line.setFillColor(sf::Color(200, 200, 200, 255));
            target.draw(line);
        }
        for (float y = fmod(OnScreenY(0), grid_size); y < (float)win_height_; y += grid_size)
        {
            sf::RectangleShape line(sf::Vector2f((float)win_width_, grid_line_width));
            line.setPosition(-grid_line_width / 2.0f, y);
            line.setFillColor(sf::Color(200, 200, 200, 255));
            target.draw(line);
        }

        sf::RenderTexture texture;
        texture.create(win_width_, win_height_);

        for (auto obj : objects_)
            if (obj->OnScreen())
                RenderObject(target, obj, texture);
        for (auto par : particles_)
            if (par->OnScreen())
                RenderObject(target, par, texture);
    }

    void Game::RenderObject(sf::RenderTarget& target, object::Object* obj, sf::RenderTexture& texture)
    {
        if (obj->opacity() == 255)
        {
            obj->Render(target);
        }
        else
        {
            texture.clear(sf::Color(0, 0, 0, 0));
            obj->Render(texture);

            alpha_shader_.setUniform("alpha", obj->opacity() / 255.0f);
            alpha_shader_.setUniform("range", std::min(2.5f, obj->radius() * 0.2f) * scale_ / win_width_);
            alpha_shader_.setUniform("scale", std::max(6.0f, 30.0f - obj->radius()));

            sf::Sprite sprite(texture.getTexture());
            sprite.setTextureRect(sf::IntRect(0, win_height_, win_width_, -(int)win_height_));

            sf::RenderStates states;
            states.shader = &alpha_shader_;
            states.blendMode = sf::BlendMode(sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha);
            target.draw(sprite, states);
        }
    }

    void Game::SetWindowSize(const sf::Vector2u& size)
    {
        win_width_ = size.x;
        win_height_ = size.y;
    }

    void Game::Spawn(object::Object* obj)
    {
        spawn_list_.push_front(obj);
    }

    void Game::SpawnObstacles(int amount, int range, int min_size, int size_range, int min_sides, int side_range)
    {
        static constexpr int colors_size = 3;
        static sf::Color colors[] = {
            sf::Color(0xdd8800ff),
            sf::Color(0xeeee99ff),
            sf::Color(0x0066ffff)
        };
        static sf::Color border_colors[] = {
            sf::Color(0x994400ff),
            sf::Color(0x888844ff),
            sf::Color(0x003399ff)
        };

        uint64_t team = -1;
        srand((unsigned int)time(0));
        for (int i = 0; i < amount; i++)
        {
            float x = rand() % range - range / 2.0f;
            float y = rand() % range - range / 2.0f;
            int r = rand() % size_range + min_size;
            uint8_t p = rand() % side_range;
            auto obj = new diep::object::Object(*this, NextId(), x, y, (float)r, p + min_sides);
            obj->SetMaxHealth(r * 4);
            if (p >= 0 && p < colors_size)
                obj->SetColor(colors[p], border_colors[p]);
            if (team == -1) team = obj->team();
            else obj->SetTeam(team);
            Spawn(obj);
        }
    }

    void Game::SpawnItems(int amount, int range)
    {
        srand((unsigned int)time(0));
        for (int i = 0; i < amount; i++)
        {
            float x = rand() % range - range / 2.0f;
            float y = rand() % range - range / 2.0f;
            Spawn(new diep::object::WeaponBall(*this, NextId(), x, y));
        }
        for (int i = 0; i < amount; i++)
        {
            float x = rand() % range - range / 2.0f;
            float y = rand() % range - range / 2.0f;
            Spawn(new diep::object::HealthBall(*this, NextId(), x, y));
        }
    }

    void Game::KeyPressed(int key)
    {
        switch (key)
        {
        case sf::Keyboard::Key::F1:
            debug_ = !debug_;
            break;
        }
    }
}
