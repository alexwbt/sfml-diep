#pragma once

#include "object.h"

namespace diep
{
	class Tank : public Object
	{
	private:
		bool controls_[4];

		float move_force_ = 2.0f;

	public:
		Tank(unsigned int id, float x, float y, float radius)
			: Object(id, x, y, radius)
		{
			type_ = Type::kTank;
		}

		void Update(float time_scale) override;

		void SetControls(bool* controls);
	};
}
