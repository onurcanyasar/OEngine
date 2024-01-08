#pragma once
#include <stdexcept>
#include <vector>

class IComponentPool
{
public:
	virtual ~IComponentPool() = default;

};
template<typename T>
class ComponentPool : public IComponentPool
{

public:
	std::vector<T> components_;
	ComponentPool(std::size_t capacity)
	{
		components_.resize(capacity);
	}

	T& getComponent(std::size_t index)
	{
		
		if (index >= components_.size())
		{
			throw std::out_of_range("Index out of range!");
		}

		return components_[index];
	}
	template<typename... Args>
	void addComponent(std::size_t index, Args&&... args)
	{
		if (index >= components_.size())
		{
			throw std::out_of_range("Index out of range!");
		}
		components_[index] = T(std::forward<Args>(args)...);
	}

	

};

