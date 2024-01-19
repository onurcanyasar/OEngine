#pragma once

#include "../Components/Transform.h"
#include <cstddef>
struct CircleCollider
{
	CircleCollider(float radius) : radius(radius) {}
	CircleCollider() = default;
	float radius { 0 };
	Transform transform {};
	bool is_colliding { false };
	std::size_t colliding_entity_id { 0 };
};
