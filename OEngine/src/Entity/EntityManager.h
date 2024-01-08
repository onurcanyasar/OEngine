#pragma once
#include <vector>
#include "EntityMemoryPool.h"



class EntityManager
{
public:
	EntityManager(EntityMemoryPool* entity_memory_pool) : entity_memory_pool_(entity_memory_pool)
	{
	}


	Entity createEntity();
	void removeEntity(Entity entity);
	void update();

private:
	EntityMemoryPool* entity_memory_pool_;
	std::vector<Entity> entities_gonna_be_removed_;
	std::vector<Entity> entities_gonna_be_added_;

};

