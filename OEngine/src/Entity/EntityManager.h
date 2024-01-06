#pragma once
#include "EntityMemoryPool.h"

class EntityManager
{
public:
	std::vector<Entity> entities;
	EntityManager(EntityMemoryPool* entity_memory_pool) : entity_memory_pool_(entity_memory_pool)
	{
		entities.resize(entity_memory_pool_->entity_capacity_);
	}


	Entity addEntity();
	void removeEntity(Entity entity);
	void update();

private:
	EntityMemoryPool* entity_memory_pool_;
	std::vector<Entity> entities_gonna_be_removed_;
	std::vector<Entity> entities_gonna_be_added_;

};

