#pragma once
#include <cstddef>


class Entity
{
public:
	std::size_t id;
	Entity(const std::size_t id) : id(id) { }
	Entity() : id(-1) { }
	
};

