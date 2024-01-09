#pragma once

struct Velocity
{

Velocity(const float x, const float y, const float angular_velocity) : x(x), y(y), angular_velocity(angular_velocity){}
float x {};
float y {};
float angular_velocity {};
Velocity() = default;

};

