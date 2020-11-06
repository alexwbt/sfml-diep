#include "collision.h"

namespace diep
{
	namespace coll
	{
		bool collide(const object::Object& obj1, const object::Object& obj2)
		{
			switch ((int)obj1.Shape() | (int)obj2.Shape())
			{
			case 0b1:
				return circleVsCircle(obj1, obj2);
				break;
			default:
				return false;
			}
		}

		bool circleVsCircle(const object::Object& obj1, const object::Object& obj2)
		{
			return pow(obj1.X() - obj2.X(), 2) + pow(obj1.Y() - obj2.Y(), 2) < pow(obj1.Radius() + obj2.Radius(), 2);
		}
	}
}
