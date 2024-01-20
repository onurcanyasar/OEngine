#include "CircleCollisonSystem.h"

void CircleCollisonSystem::update()
{
	for (const auto i : entity_memory_pool_->entity_set.dense_vec)
	{
		std::size_t entity_id = entity_memory_pool_->entity_set.dense_vec[i];
		auto& transform = entity_memory_pool_->getComponent<Transform>(entity_id);
		const auto& circle_collider = entity_memory_pool_->getComponent<CircleCollider>(entity_id);
		auto& velocity = entity_memory_pool_->getComponent<Velocity>(entity_id);

		for (const auto j : entity_memory_pool_->entity_set.dense_vec)
		{
			
			std::size_t entity_id2 = entity_memory_pool_->entity_set.dense_vec[j];
			if (entity_id2 == entity_id) continue;

			auto& transform2 = entity_memory_pool_->getComponent<Transform>(entity_id2);
			const auto& circle_collider2 = entity_memory_pool_->getComponent<CircleCollider>(entity_id2);
			auto& velocity2 = entity_memory_pool_->getComponent<Velocity>(entity_id2);
			float sum_of_radii = circle_collider.radius + circle_collider2.radius;
			float distance_without_sqrt = (transform.position.x - transform2.position.x) * (transform.position.x - transform2.position.x) + (transform.position.y - transform2.position.y) * (transform.position.y - transform2.position.y);
			distance_without_sqrt = fabs(distance_without_sqrt);
			sum_of_radii = sum_of_radii * sum_of_radii;
			
			if (distance_without_sqrt < sum_of_radii)
			{
				const float distance = sqrtf(distance_without_sqrt);
				float overlap = (distance - circle_collider.radius - circle_collider2.radius) / 2;


				float normal_x = (transform.position.x - transform2.position.x) / distance;
				float normal_y = (transform.position.y - transform2.position.y) / distance;

				float tangent_x = -normal_y;
				float tangent_y = normal_x;

				float dot_tangent1 = velocity.x * tangent_x + velocity.y * tangent_y;
				float dot_tangent2 = velocity2.x * tangent_x + velocity2.y * tangent_y;

				float dot_normal1 = velocity.x * normal_x + velocity.y * normal_y;
				float dot_normal2 = velocity2.x * normal_x + velocity2.y * normal_y;

				float mass = 1.0f;

				float m1 = (dot_normal1 * (mass - mass) + 2.0f * mass * dot_normal2) / (mass + mass);
				float m2 = (dot_normal2 * (mass - mass) + 2.0f * mass * dot_normal1) / (mass + mass);



				transform.position.x -= overlap * (transform.position.x - transform2.position.x) / distance;
				transform.position.y -= overlap * (transform.position.y - transform2.position.y) / distance;
				transform2.position.x += overlap * (transform.position.x - transform2.position.x) / distance;
				transform2.position.y += overlap * (transform.position.y - transform2.position.y) / distance;


				velocity.x = tangent_x * dot_tangent1 + normal_x * m1;
				velocity.y = tangent_y * dot_tangent1 + normal_y * m1;

				velocity2.x = tangent_x * dot_tangent2 + normal_x * m2;
				velocity2.y = tangent_y * dot_tangent2 + normal_y * m2;


			}
			
		}


	}
}
