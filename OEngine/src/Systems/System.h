#pragma once
#include <memory>

#include "../Entity/EntityMemoryPool.h"

class System
{
public:
	friend class SystemManager;
	virtual ~System() = default;
	System() = default;

	virtual void update() = 0;

	System(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool)
	: entity_memory_pool_(entity_memory_pool),
	entities_(entity_memory_pool_->entity_set.capacity) {}

	void addEntity(Entity entity)
	{
		entities_.insert(entity.id);
	}
	void removeEntity(Entity entity)
	{
		entities_.remove(entity.id);
	}

protected:
	std::shared_ptr<EntityMemoryPool> entity_memory_pool_;
	SparseSet entities_;

};

