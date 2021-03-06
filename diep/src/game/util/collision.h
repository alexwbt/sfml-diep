#pragma once

namespace diep
{
	namespace object {
		class Object;
	}

	struct Point
	{
		float x, y;
	};

	namespace coll
	{
		bool collide(object::Object& obj1, object::Object& obj2);

		bool circle_vs_circle(object::Object& obj1, object::Object& obj2);
		bool polygon_vs_polygon(object::Object& obj1, object::Object& obj2);
		bool circle_vs_polygon(object::Object& obj1, object::Object& obj2);
		bool point_in_polygon(float x, float y, const std::vector<Point>& points);
        bool point_in_circle(float radius, float cx, float cy, float x, float y);
        bool circle_vs_line(float radius, float cx, float cy, float x1, float y1, float x2, float y2);
        bool circle_vs_rect(float radius, float cx, float cy, float rx1, float ry1, float rx2, float ry2);

		std::shared_ptr<std::vector<Point>> polygon_get_points(float x, float y, float radius, float points, float rotate);
	}
}
