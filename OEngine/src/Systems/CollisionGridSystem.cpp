#include "CollisionGridSystem.h"

#include "../Components/CircleCollider.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Game.h"

void CollisionGridSystem::update()
{
	grid_->clear();
	for (std::size_t i = 0; i < entities_.dense_end; i++)
	{
		const std::size_t entity_id = entities_.dense_vec[i];
		const auto& transform = entity_memory_pool_->getComponent<Transform>(entity_id);
		const auto& collider = entity_memory_pool_->getComponent<CircleCollider>(entity_id);

		const int start_row = static_cast<int>(transform.position.y - collider.radius) / grid_->getCellSize();
		const int end_row = static_cast<int>(transform.position.y + collider.radius) / grid_->getCellSize();
		const int start_col = static_cast<int>(transform.position.x - collider.radius) / grid_->getCellSize();
		const int end_col = static_cast<int>(transform.position.x + collider.radius) / grid_->getCellSize();

		for (int row = start_row; row <= end_row; row++)
		{
			for (int col = start_col; col <= end_col; col++)
			{
				if (row >= 0 && row < grid_->getNumRows() && col >= 0 && col < grid_->getNumCols())
				{
					grid_->cells[row][col].push_back(entity_id);
					/*std::cout << "entities : ";
					for (const auto i : grid_.cells[row][col])
					{
						std::cout << i << " ";
					}
					std::cout << "row: " << row << " col: " << col << std::endl;*/
					
				}
			}
		}




	}

	for (const auto& row : grid_->cells)
	{
		for (const auto& col : row)
		{
			for (const auto entity_id : col)
			{
				
				auto& transform = entity_memory_pool_->getComponent<Transform>(entity_id);
				const auto& circle_collider = entity_memory_pool_->getComponent<CircleCollider>(entity_id);
				auto& velocity = entity_memory_pool_->getComponent<Velocity>(entity_id);

				for (const auto entity_id2 : col)
				{

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
						const float overlap = (distance - circle_collider.radius - circle_collider2.radius) / 2;


						/*const float normal_x = (transform.position.x - transform2.position.x) / distance;
						const float normal_y = (transform.position.y - transform2.position.y) / distance;

						const float tangent_x = -normal_y;
						const float tangent_y = normal_x;

						const float dot_tangent1 = velocity.x * tangent_x + velocity.y * tangent_y;
						const float dot_tangent2 = velocity2.x * tangent_x + velocity2.y * tangent_y;



						const float dot_normal1 = velocity.x * normal_x + velocity.y * normal_y;
						const float dot_normal2 = velocity2.x * normal_x + velocity2.y * normal_y;

						constexpr float mass = 200.0f;

						const float m1 = (dot_normal1 * (mass - mass) + 2.0f * mass * dot_normal2) / (mass + mass);
						const float m2 = (dot_normal2 * (mass - mass) + 2.0f * mass * dot_normal1) / (mass + mass);
						


						transform.position.x -= overlap * (transform.position.x - transform2.position.x) / distance;
						transform.position.y -= overlap * (transform.position.y - transform2.position.y) / distance;
						transform2.position.x += overlap * (transform.position.x - transform2.position.x) / distance;
						transform2.position.y += overlap * (transform.position.y - transform2.position.y) / distance;


						velocity.x = tangent_x * dot_tangent1 + normal_x * dot_normal2;
						velocity.y = tangent_y * dot_tangent1 + normal_y * dot_normal2;

						velocity2.x = tangent_x * dot_tangent2 + normal_x * dot_normal1;
						velocity2.y = tangent_y * dot_tangent2 + normal_y * dot_normal1;
*/

						const auto normal = glm::normalize(transform.position - transform2.position);
						const auto tangent = glm::vec2(-normal.y, normal.x);

						const auto dot_tangent1 = glm::dot(glm::vec2(velocity.x, velocity.y), tangent);
						const auto dot_tangent2 = glm::dot(glm::vec2(velocity2.x, velocity2.y), tangent);

						const auto dot_normal1 = glm::dot(glm::vec2(velocity.x, velocity.y), normal);
						const auto dot_normal2 = glm::dot(glm::vec2(velocity2.x, velocity2.y), normal);

						const float mass1 = circle_collider.radius;
						const float mass2 = circle_collider2.radius;

						const auto m1 = (mass1 - mass2) / (mass1 + mass2) * dot_normal1 + (2.0f * mass2) / (mass1 + mass2) * dot_normal2;
						const auto m2 = (mass2 - mass1) / (mass1 + mass2) * dot_normal2 + (2.0f * mass1) / (mass1 + mass2) * dot_normal1;
						/*const float m1 = (dot_normal1 * (mass1 - mass2) + 2.0f * mass2 * dot_normal2) / (mass1 + mass2);
						const float m2 = (dot_normal2 * (mass2 - mass1) + 2.0f * mass1 * dot_normal1) / (mass1 + mass2);*/


						transform.position -= normal * overlap;
						transform2.position += normal * overlap;

						const auto v1 = tangent * dot_tangent1 + normal * m1;
						const auto v2 = tangent * dot_tangent2 + normal * m2;

						velocity.x = v1.x;
						velocity.y = v1.y;

						velocity2.x = v2.x;
						velocity2.y = v2.y;


						

						


						

					}

				}
				
			}
		}
	}
}
