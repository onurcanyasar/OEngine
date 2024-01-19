#pragma once
#include "System.h"
#include "../Components/CircleCollider.h"
#include "../Components/Transform.h"
class CircleCollisonSystem : public System
{
public:
	CircleCollisonSystem(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool) : System(entity_memory_pool) {}
	void update() override;
};
