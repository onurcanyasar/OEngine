#pragma once
#include "System.h"
#include "../Components/CircleCollider.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Velocity.hpp"
class CircleCollisionSystem : public System
{
public:
	explicit CircleCollisionSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;
};
