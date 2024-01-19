#pragma once
#include <memory>

#include "../Entity/EntityMemoryPool.h"

class System
{
public:
	virtual ~System() = default;
	System() = default;
	virtual void update() = 0;
	System(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool) : entity_memory_pool_(entity_memory_pool) {}
protected:
	std::shared_ptr<EntityMemoryPool> entity_memory_pool_;
};

