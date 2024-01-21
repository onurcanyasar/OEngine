#pragma once
#include "System.h"
#include "../Entity/EntityMemoryPool.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"


class SpriteSystem : public System
{

public:
	SpriteSystem() = default;

	explicit SpriteSystem(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool)
		: System(entity_memory_pool)
	{
	}

	void update() override;

	
};

