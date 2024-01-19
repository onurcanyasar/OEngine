#pragma once
#include <memory>
#include "../Entity/EntityMemoryPool.h"
#include "../Components/Collider2D.h"
#include "../Components/Velocity.h"
#include "../Components/Transform.h"
class ColliderSystem
{
public:
	ColliderSystem(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool) : entity_memory_pool_(entity_memory_pool) {}
	void update();

private:
	std::shared_ptr<EntityMemoryPool> entity_memory_pool_;
};

