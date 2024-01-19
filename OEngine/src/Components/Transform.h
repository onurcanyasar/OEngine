#pragma once
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

struct Transform

{
public:
	Transform()
	{
		std::cout << "Transform ctor called" << std::endl;
	}
	~Transform()
	{
		std::cout << "Transform dtor called" << std::endl;
	
	}
	glm::vec2 position;
	glm::vec2 prev_position;
	float rotation;
	friend std::ostream& operator<<(std::ostream& os, const Transform& transform);


};


inline std::ostream& operator<<(std::ostream& os, const Transform& transform)
{
	os << "{" << transform.position.x << ", " << transform.position.y << "}";
	return os;
}