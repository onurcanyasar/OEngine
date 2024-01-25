#pragma once
#include <memory>
#include "../Entity/EntityMemoryPool.h"
#include "../Components/RectCollider.h"
#include "../Components/Velocity.h"
#include "../Components/Transform.h"
#include "System.h"
class ColliderSystem : public System
{
public:
	explicit ColliderSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;

private:
	
};

