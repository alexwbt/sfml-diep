#pragma once

#include "component.h"

namespace diep
{
	namespace weapon
	{
		class Cannon : public Component
		{
		public:
			using Component::Component;

			void Fire() override;
		};
	}
}
