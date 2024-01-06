#pragma once

#include "../Entity/EntityMemoryPool.h""
#include "../Components/Transform.h""
#include "../Components/Velocity.h"
class MoveSystem
{
public:
	MoveSystem(EntityMemoryPool* entity_memory_pool) : entity_memory_pool_(entity_memory_pool)
	{}

	void update();

private:
	EntityMemoryPool* entity_memory_pool_;
};

