#pragma once
#include <iostream>
#include <ostream>
#include <string>

#include "Component.h"

class Test : public Component
{
public:
	Test() = default;
	~Test()
	{
		std::cout << "Test destroyed " << name << std::endl;
	}
	Test(const std::string& name) : name(name) {}
	std::string& getName() { return name; }

private:
	std::string name;
};

