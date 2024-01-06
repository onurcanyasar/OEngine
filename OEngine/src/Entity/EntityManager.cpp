#include "EntityManager.h"

Entity EntityManager::addEntity()
{
	const Entity e = entity_memory_pool_->createEntity();
	return e;
}

void EntityManager::removeEntity(const Entity entity) 
{
	entities_gonna_be_removed_.push_back(entity);
	
}

void EntityManager::update()
{

	for (const auto& entity : entities_gonna_be_removed_)
	{
		entity_memory_pool_->removeEntity(entity.id);
	}

	entities_gonna_be_added_.clear();
	entities_gonna_be_removed_.clear();
}
