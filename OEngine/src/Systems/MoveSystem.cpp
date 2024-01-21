#include "MoveSystem.h"



void MoveSystem::update(float deltaTime) const
{

	for (std::size_t id = 1; id <= entity_memory_pool_->entity_set.dense_end; id++)
	{


		auto& transform = entity_memory_pool_->getComponent<Transform>(id);
		auto& velocity = entity_memory_pool_->getComponent<Velocity>(id);
		auto& collider = entity_memory_pool_->getComponent<RectCollider>(id);
		//std::cout << "id: " << id  << " velocity: " << velocity.x << std::endl;

		transform.rotation += velocity.angular_velocity * deltaTime;
		transform.prev_position = transform.position;

		transform.position.x += velocity.x * deltaTime;
		transform.position.y += velocity.y * deltaTime;

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
