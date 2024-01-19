#include "MoveSystem.h"



void MoveSystem::update() const
{

	//for (std::size_t id = 0; id < entity_memory_pool_->active_vector.size(); id++)
	//{
	//	if (entity_memory_pool_->active_vector[id]) //TODO: gonna change this, this is inefficient. Start from the last active entity and go backwards.
	//	{
	//		
	//		auto& transform = entity_memory_pool_->getComponent<Transform>(id);
	//		auto& velocity = entity_memory_pool_->getComponent<Velocity>(id);
	//		auto& collider = entity_memory_pool_->getComponent<Collider2D>(id);

	//		transform.rotation += velocity.angular_velocity;
	//		transform.prev_position = transform.position;

	//		transform.position.x += velocity.x;
	//		transform.position.y += velocity.y;

	//		collider.collider_rect.x = transform.position.x;
	//		collider.collider_rect.y = transform.position.y;

	//		if (transform.position.x < 0)
	//		{
	//			transform.position.x = 0;
	//			velocity.x = -velocity.x;
	//		}
	//		else if (transform.position.x > 800)
	//		{
	//			transform.position.x = 800;
	//			velocity.x = -velocity.x;
	//		}
	//		if (transform.position.y < 0)
	//		{
	//			transform.position.y = 0;
	//			velocity.y = -velocity.y;
	//		}
	//		else if (transform.position.y > 600)
	//		{
	//			transform.position.y = 600;
	//			velocity.y = -velocity.y;
	//		}
	//		

	//		
	//	}
	//}

	for (std::size_t id = 1; id <= entity_memory_pool_->entity_set.dense_end; id++)
	{
		
		auto& transform = entity_memory_pool_->getComponent<Transform>(id);
		auto& velocity = entity_memory_pool_->getComponent<Velocity>(id);
		auto& collider = entity_memory_pool_->getComponent<Collider2D>(id);
		//std::cout << "id: " << id  << " velocity: " << velocity.x << std::endl;
		transform.rotation += velocity.angular_velocity;
		transform.prev_position = transform.position;

		transform.position.x += velocity.x;
		transform.position.y += velocity.y;

		collider.collider_rect.x = transform.position.x;
		collider.collider_rect.y = transform.position.y;

		if (transform.position.x < 0)
		{
			transform.position.x = 0;
			velocity.x = -velocity.x;
		}
		else if (transform.position.x > 800)
		{
							transform.position.x = 800;
			velocity.x = -velocity.x;
		}
		if (transform.position.y < 0)
		{
							transform.position.y = 0;
			velocity.y = -velocity.y;
		}
		else if (transform.position.y > 600)
		{
							transform.position.y = 600;
			velocity.y = -velocity.y;
		}
		
	}
}
