#pragma once
#include <SDL_render.h>

#include "System.h"
#include "../Components/Circle.h"
#include "../Components/Transform.h"
#include "../Game.h"

class CircleRenderSystem : public System
{
public:
	explicit CircleRenderSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;
	
private:
	void drawCircle(SDL_Renderer* renderer, float center_x, float center_y, float radius);
	void drawCircleCosSin(SDL_Renderer* renderer, float center_x, float center_y, float radius);
};
