#include "CircleCollisonSystem.h"

void CircleCollisonSystem::update()
{
	for (const auto i : entity_memory_pool_->entity_set.dense_vec)
	{
		std::size_t entity_id = entity_memory_pool_->entity_set.dense_vec[i];
		const auto& transform = entity_memory_pool_->getComponent<Transform>(entity_id);
		const auto& circle_collider = entity_memory_pool_->getComponent<CircleCollider>(entity_id);

		for (const auto j : entity_memory_pool_->entity_set.dense_vec)
		{
			
			std::size_t entity_id2 = entity_memory_pool_->entity_set.dense_vec[j];
			if (entity_id2 == entity_id) continue;

			const auto& transform2 = entity_memory_pool_->getComponent<Transform>(entity_id2);
			const auto& circle_collider2 = entity_memory_pool_->getComponent<CircleCollider>(entity_id2);

			float sum_of_radii = circle_collider.radius + circle_collider2.radius;
			float distance = glm::distance(transform.position, transform2.position);
			
			if (distance < sum_of_radii)
			{
				std::cout << "colliding" << std::endl;
			}
			
		}


	}
}
