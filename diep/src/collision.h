#pragma once

#include "object\object.h"

namespace diep
{
	namespace coll
	{
		bool collide(const object::Object& obj1, const object::Object& obj2);

		bool circleVsCircle(const object::Object& obj1, const object::Object& obj2);
	}
}
