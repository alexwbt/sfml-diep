#pragma once

namespace diep
{
	namespace coll
	{
		bool collide(const object::Object& obj1, const object::Object& obj2);

		bool circle_vs_circle(const object::Object& obj1, const object::Object& obj2);
		bool polygon_vs_polygon(const object::Object& obj1, const object::Object& obj2);
		bool circle_vs_polygon(const object::Object& obj1, const object::Object& obj2);
	}
}
