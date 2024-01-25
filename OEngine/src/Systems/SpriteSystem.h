#pragma once
#include "System.h"
#include "../Entity/EntityMemoryPool.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"


class SpriteSystem : public System
{

public:
	explicit SpriteSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;

	
};

