#include "MoveSystem.h"

#include "../Entity/EntityMemoryPool.h"
#include "../Components/Transform.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/RectCollider.hpp"

void MoveSystem::update()
{

	for (std::size_t i = 0; i < entities_.dense_end; i++) {
	
		const std::size_t id = entities_.dense_vec[i];
		auto& transform = entity_memory_pool_->getComponent<Transform>(id);
		auto& velocity = entity_memory_pool_->getComponent<Velocity>(id);
		auto& collider = entity_memory_pool_->getComponent<RectCollider>(id);
		//std::cout << "id: " << id  << " velocity: " << velocity.x << std::endl;

		transform.rotation += velocity.angular_velocity * delta_time_;
		transform.prev_position = transform.position;

		transform.position.x += velocity.x * delta_time_;
		transform.position.y += velocity.y * delta_time_;

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
