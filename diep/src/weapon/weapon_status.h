#pragma once

#include "../object/object.h"

namespace diep
{
    namespace weapon
    {
		struct WeaponStatus
		{
			const object::Object* owner;
			bool firing = false;
			float reload_speed = 30.0f;
			float bullet_speed = 2.0f;
			int bullet_lifetime = 100;
		};
    }
}
