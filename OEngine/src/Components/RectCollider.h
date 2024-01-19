#pragma once
#include <SDL_rect.h>
#include <cstddef>
#include <glm/vec2.hpp>

struct RectCollider
{
	SDL_FRect collider_rect {};
	bool is_colliding { false };
	std::size_t colliding_entity_id { 0 };
	RectCollider(float w, float h) : collider_rect({ 0, 0, w, h }) {}
	RectCollider() = default;
};

