#pragma once
#include <memory>

#include "../Entity/EntityMemoryPool.h"

class System
{
public:
	friend class SystemManager;
	virtual ~System() = default;

	virtual void update() = 0;

	explicit System(EntityMemoryPool* entity_memory_pool)
	: entities_(entity_memory_pool->entity_set.capacity), entity_memory_pool_(entity_memory_pool) {}

	void addEntity(Entity entity)
	{
		entities_.insert(entity.id);
	}
	void removeEntity(Entity entity)
	{
		entities_.remove(entity.id);
	}

protected:
	SparseSet entities_;
	EntityMemoryPool* entity_memory_pool_;

};

