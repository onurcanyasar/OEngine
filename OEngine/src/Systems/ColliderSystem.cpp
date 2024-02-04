#include "ColliderSystem.h"

void ColliderSystem::update()
{
	for (std::size_t i = 0; i < entities_.dense_end; i++) {
		const std::size_t id = entities_.dense_vec[i];
		if (!entity_memory_pool_->active_vector[id]) continue;
		
		auto& collider = entity_memory_pool_->getComponent<RectCollider>(id);
		auto& velocity = entity_memory_pool_->getComponent<Velocity>(id);
		auto& transform = entity_memory_pool_->getComponent<Transform>(id);
		//compare with other colliders
		for (std::size_t id2 = 0; id2 < entity_memory_pool_->active_vector.size(); id2++)
		{
			if (!entity_memory_pool_->active_vector[id2]) continue;

			if (id != id2)
				{
				auto& collider2 = entity_memory_pool_->getComponent<RectCollider>(id2);
				
				if (collider.collider_rect.x < collider2.collider_rect.x + collider2.collider_rect.w &&
					collider.collider_rect.x + collider.collider_rect.w > collider2.collider_rect.x &&
					collider.collider_rect.y < collider2.collider_rect.y + collider2.collider_rect.h &&
					collider.collider_rect.y + collider.collider_rect.h > collider2.collider_rect.y)
				{

					/*float overlap_x = std::min(collider.collider_rect.x + collider.collider_rect.w, collider2.collider_rect.x + collider2.collider_rect.w) - std::max(collider.collider_rect.x, collider2.collider_rect.x);
					float overlap_y = std::min(collider.collider_rect.y + collider.collider_rect.h, collider2.collider_rect.y + collider2.collider_rect.h) - std::max(collider.collider_rect.y, collider2.collider_rect.y);*/

					collider.is_colliding = true;
					collider.colliding_entity_id = id2;
					
					//std::cout << id << " colliding with " << id2 << std::endl;
					//transform.position = transform.position - glm::vec2(overlap_x, overlap_y);
					velocity.x = -velocity.x;
					velocity.y = -velocity.y;
				}
				else
				{
					collider.is_colliding = false;
					collider.colliding_entity_id = 0;
				}
			}
		}
	}
}
