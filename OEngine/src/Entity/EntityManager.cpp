#include "EntityManager.h"

Entity EntityManager::createEntity() 
{
	const std::size_t id = entity_memory_pool_->getAvailableEntityID();
	const Entity e(id);
	entities_gonna_be_added_.push_back(e);
	return e;
}


void EntityManager::removeEntity(const Entity entity) 
{
	entities_gonna_be_removed_.push_back(entity);
	
}

void EntityManager::update()
{

	for (const auto& entity : entities_gonna_be_added_)
	{
		entity_memory_pool_->registerEntity(entity);
	}
	for (const auto& entity : entities_gonna_be_removed_)
	{
		entity_memory_pool_->removeEntity(entity.id);
	}

	entities_gonna_be_added_.clear();
	entities_gonna_be_removed_.clear();
}
