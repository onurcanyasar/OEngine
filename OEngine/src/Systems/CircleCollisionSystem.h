﻿#pragma once
#include "System.h"
#include "../Components/CircleCollider.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
class CircleCollisionSystem : public System
{
public:
	explicit CircleCollisionSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;
};
