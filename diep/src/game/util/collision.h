#pragma once

namespace diep
{
	namespace coll
	{
		bool collide(const object::Object& obj1, const object::Object& obj2);

		bool circle_vs_circle(const object::Object& obj1, const object::Object& obj2);
		bool polygon_vs_polygon(const object::Object& obj1, const object::Object& obj2);
		bool circle_vs_polygon(const object::Object& obj1, const object::Object& obj2);
		bool point_in_polygon(float x, float y, const std::vector<sf::Vector2f>& points);
        bool point_in_circle(float radius, float cx, float cy, float x, float y);
        bool circle_vs_line(float radius, float cx, float cy, float x1, float y1, float x2, float y2);
        bool circle_vs_rect(float radius, float cx, float cy, float rx1, float ry1, float rx2, float ry2);
	}
}
