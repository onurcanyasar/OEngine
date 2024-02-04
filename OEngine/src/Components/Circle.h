#pragma once
struct Circle
{
	Circle(float radius) : radius(radius) {}
	Circle() = default;
	float radius { 0 };
};