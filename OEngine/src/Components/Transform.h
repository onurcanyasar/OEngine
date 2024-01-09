#pragma once
#include <ostream>
#include <glm/glm.hpp>

struct Transform

{
public:
	Transform() = default;
	~Transform() = default;
	glm::vec2 position;
	float rotation;
	friend std::ostream& operator<<(std::ostream& os, const Transform& transform);


};


inline std::ostream& operator<<(std::ostream& os, const Transform& transform)
{
	os << "{" << transform.position.x << ", " << transform.position.y << "}";
	return os;
}