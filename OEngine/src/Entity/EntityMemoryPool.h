#pragma once
#include <cstddef>
#include <queue>
#include <vector>

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Entity.h"
#include "../IComponentPool.h"
#include "../Utility/SparseSet.h"

class EntityMemoryPool
{
public:
	friend class EntityManager;

	Entity createEntity() //simple creation, handy in before entering the main loop
	{
		const auto entity_id = getAvailableEntityID();
		const Entity e(entity_id);

		entity_set.insert(entity_id);
		active_vector[entity_id] = true;
		active_entity_count_++;
		return e;
	}

	void registerEntity(Entity entity) //registering an entity that was created outside of the memory pool
	{
		entity_set.insert(entity.id);
		active_vector[entity.id] = true;
		active_entity_count_++;
	}

	
	void removeEntity(const std::size_t entity_id) 
	{
		available_entity_ids_.emplace_front(entity_id);
		active_vector[entity_id] = false;
		active_entity_count_--;
		entity_set.remove(entity_id);
	}

	std::size_t getAvailableEntityID()
	{
		if (available_entity_ids_.empty())
		{
			resize(entity_capacity_ + 50);
		}
		const std::size_t entity_id = available_entity_ids_.front();
		available_entity_ids_.pop_front();
		return entity_id;
	}

	EntityMemoryPool(const std::size_t entity_capacity)
		: entity_set(entity_capacity), entity_capacity_(entity_capacity)
	{
		active_vector.resize(entity_capacity_);
		
		for (std::size_t i = 1; i <= entity_capacity_; i++)
		{
			available_entity_ids_.emplace_back(i);
		}
		
	}

	template <typename T>
	void registerComponentType()
	{

		const auto typeIndex = std::type_index(typeid(T));
		
		if (components_.find(typeIndex) != components_.end())
		{
			throw std::runtime_error("Component type already registered.");
		}
		
		components_[typeIndex] = std::make_shared<ComponentPool<T>>(entity_capacity_);
		component_types_.push_back(typeIndex);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		return getComponentPool<T>()->getComponent(entity.id);
	}

	template<typename T, typename... Args>
	void addComponent(Entity entity, Args&&... args)
	{
		const auto typeIndex = std::type_index(typeid(T));

		getComponentPool<T>()->addComponent(entity.id, std::forward<Args>(args)...);
	}

	
	std::vector<bool> active_vector;
	SparseSet entity_set;

	template<typename T>
	std::shared_ptr<ComponentPool<T>> getComponentPool()
	{
		const auto typeIndex = std::type_index(typeid(T));


		return std::static_pointer_cast<ComponentPool<T>>(components_[typeIndex]);
	}

	
private:
	std::deque<std::size_t> available_entity_ids_;
	std::size_t active_entity_count_{ 0 };
	std::size_t entity_capacity_{ 0 };
	
	std::unordered_map<std::type_index, std::shared_ptr<IComponentPool>> components_;
	std::vector<std::type_index> component_types_; 

	

	void resizeIfNecessary(std::size_t new_entity_id)
	{
		if (new_entity_id + 1 > entity_capacity_)
		{
			resize(entity_capacity_ + 50);
		}
	}
	void resize(const std::size_t new_entity_capacity)
	{
		std::cout << "resizing entity memory pool" << std::endl;
		for (std::size_t i = entity_capacity_; i < new_entity_capacity; i++)
		{
			available_entity_ids_.emplace_back(i);
		}
		entity_capacity_ = new_entity_capacity;
		active_vector.resize(entity_capacity_);
		

		for (const auto& typeIndex : component_types_)
		{
			components_[typeIndex]->resize(entity_capacity_);
		}

	}


};

