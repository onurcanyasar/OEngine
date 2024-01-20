#pragma once
#include <SDL_render.h>

#include "System.h"
#include "../Components/Circle.h"
#include "../Components/Transform.h"
#include "../Game.h"

class CircleRenderSystem : public System
{
public:
	void update() override;
	CircleRenderSystem(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool) : System(entity_memory_pool) {}
private:
	void drawCircle(SDL_Renderer* renderer, float center_x, float center_y, float radius);
	void drawCircleCosSin(SDL_Renderer* renderer, float center_x, float center_y, float radius);
};
