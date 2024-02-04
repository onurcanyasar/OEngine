#pragma once
#include "System.h"
#include "../Components/Transform.hpp"
class ClickToMoveSystem : public System
{
public:
	explicit ClickToMoveSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;
};

