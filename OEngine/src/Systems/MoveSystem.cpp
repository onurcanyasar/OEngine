#include "MoveSystem.h"



void MoveSystem::update() const
{

	for (std::size_t id = 0; id < entity_memory_pool_->active_vector.size(); id++)
	{
		if (entity_memory_pool_->active_vector[id]) //TODO: gonna change this, this is inefficient. Start from the last active entity and go backwards.
		{
			
			auto& transform = entity_memory_pool_->getComponent<Transform>(id);
			auto& velocity = entity_memory_pool_->getComponent<Velocity>(id);
			transform.rotation += velocity.angular_velocity;
			transform.position.x += velocity.x;
			transform.position.y += velocity.y;
			

			
		}
	}
}
