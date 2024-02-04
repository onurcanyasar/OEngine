#pragma once

#include "System.h"

class MoveSystem : public System
{
public:
	MoveSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;

	void updateDeltaTime(float delta_time)
	{
		this->delta_time_ = delta_time;
	}
private:
	float delta_time_ {};
};

