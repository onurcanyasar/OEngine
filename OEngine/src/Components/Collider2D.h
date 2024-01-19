#pragma once
#include <SDL_rect.h>
#include <cstddef>
#include <glm/vec2.hpp>

struct Collider2D
{
	SDL_FRect collider_rect {};
	bool is_colliding { false };
	std::size_t colliding_entity_id { 0 };
	Collider2D(float w, float h) : collider_rect({ 0, 0, w, h }) {}
	Collider2D() = default;
};

