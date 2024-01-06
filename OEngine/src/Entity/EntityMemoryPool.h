#pragma once
#include <cstddef>
#include <queue>
#include <vector>

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Entity.h"
#include "../IComponentPool.h"

class EntityMemoryPool
{
public:
	friend class EntityManager;

	Entity createEntity()
	{
		const auto entity_id = getAvailableEntityID();
		active_entity_count_++;
		const Entity e(entity_id);
		active_vector_[entity_id] = true;
		return e;

	}

	void removeEntity(const std::size_t entity_id)
	{
		active_entity_count_--;
		available_entity_ids_.push(entity_id);
		active_vector_[entity_id] = false;
	}

	std::size_t getAvailableEntityID()
	{
		const std::size_t entity_id = available_entity_ids_.front();
		available_entity_ids_.pop();
		return entity_id;
	}

	EntityMemoryPool(const std::size_t entity_capacity) : entity_capacity_(entity_capacity)
	{
		active_vector_.resize(entity_capacity_);
		//entities_.resize(entity_capacity_);
		
		for (std::size_t i = 0; i < entity_capacity_; i++)
		{
			available_entity_ids_.push(i);
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
	}
	template<typename T>
	T& getComponent(Entity entity)
	{
		return getComponentPool<T>()->getComponent(entity.id);
	}
	template<typename T>
	T& getComponent(std::size_t id)
	{
		return getComponentPool<T>()->getComponent(id);
	}

	template<typename T, typename... Args>
	void addComponent(Entity entity, Args&&... args)
	{
		const auto typeIndex = std::type_index(typeid(T));

		getComponentPool<T>()->addComponent(entity.id, std::forward<Args>(args)...);
	}
	template<typename T>
	std::shared_ptr<ComponentPool<T>> getComponentPool()
	{
		const auto typeIndex = std::type_index(typeid(T));


		return std::static_pointer_cast<ComponentPool<T>>(components_[typeIndex]);
	}
	std::vector<bool> active_vector_;

	
private:
	std::queue<std::size_t> available_entity_ids_;
	std::size_t active_entity_count_{ 0 };
	std::size_t entity_capacity_{ 0 };
	//std::vector<Entity> entities_;
	std::unordered_map<std::type_index, std::shared_ptr<IComponentPool>> components_;

	


};

