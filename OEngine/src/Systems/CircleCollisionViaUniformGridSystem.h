#pragma once
#include "System.h"

class CircleCollisionViaUniformGridSystem : public System
{
public:
	explicit CircleCollisionViaUniformGridSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;
};
