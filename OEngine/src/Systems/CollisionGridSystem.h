#pragma once
#include "System.h"
#include "../Utility/Grid.h"

class CollisionGridSystem : public System
{
public:
	CollisionGridSystem() = default;

	explicit CollisionGridSystem(std::shared_ptr<EntityMemoryPool> const& entity_memory_pool, int num_rows, int num_cols, int cell_size)
		: System(entity_memory_pool), grid_(num_rows, num_cols, cell_size)
	{
	}

	void update() override;
	Grid<std::size_t> grid_;
private:
	
};
