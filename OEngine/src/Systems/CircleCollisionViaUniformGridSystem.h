#pragma once
#include "System.h"

class CircleCollisionViaUniformGridSystem : public System
{
public:
	CircleCollisionViaUniformGridSystem() = default;

	explicit CircleCollisionViaUniformGridSystem(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;
};
