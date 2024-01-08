#include "MoveSystem.h"



void MoveSystem::update()
{

	for (std::size_t id = 0; id < entity_memory_pool_->active_vector.size(); id++)
	{
		if (entity_memory_pool_->active_vector[id])
		{
			
			auto& transform = entity_memory_pool_->getComponent<Transform>(id);
			auto& velocity = entity_memory_pool_->getComponent<Velocity>(id);
			transform.rotation += velocity.angular_velocity;
			transform.position.x += velocity.x;
			transform.position.y += velocity.y;
			//float random = (rand() % 100) / 30.0f;
			//	transform.position.y += randomVal;

			
		}
	}
}
