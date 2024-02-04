#pragma once
#include "System.h"
#include "../Entity/EntityMemoryPool.h"
#include "../Components/Sprite.hpp"
#include "../Components/Transform.hpp"


class SpriteSystem : public System
{

public:
	explicit SpriteSystem(EntityMemoryPool* entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;

	
};

