#pragma once

#include "object\object.h"

namespace diep
{
	namespace coll
	{
		bool collide(const Object& obj1, const Object& obj2);

		bool circleVsCircle(const Object& obj1, const Object& obj2);
	}
}
