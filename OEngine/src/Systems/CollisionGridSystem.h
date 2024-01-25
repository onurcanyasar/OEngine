#pragma once
#include "System.h"
#include "../Utility/Grid.h"

class CollisionGridSystem : public System
{
public:
	CollisionGridSystem(EntityMemoryPool* entity_memory_pool, Grid<std::size_t>* grid)
		: System(entity_memory_pool),
		  grid_(grid)
	{
	}

	void update() override;
	Grid<std::size_t>* grid_;
private:
	

};
