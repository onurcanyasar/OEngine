#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

class IComponentPool 
{
public:
	virtual ~IComponentPool() = default;
	virtual void resize(std::size_t new_size) = 0;


};
template<typename T>
class ComponentPool : public IComponentPool
{

public:
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
		components_[index] = std::move(T(args...));
	}

	void resize(std::size_t new_size) override
	{
		components_.resize(new_size);
	}

private:
	std::vector<T> components_;


};

/*All functions are defined in the header file because most of them are templates and the usage of this class is
makes more sense as a header only library.*/



