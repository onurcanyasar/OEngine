#pragma once
#include "../Entity/EntityMemoryPool.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"


class SpriteSystem
{

public:
	SpriteSystem(EntityMemoryPool* entity_memory_pool) : entity_memory_pool_(entity_memory_pool) {}

	void render();

private:
	EntityMemoryPool* entity_memory_pool_;
};

