#pragma once
#include <iostream>
#include <memory>
#include <SDL_render.h>
#include <glm/vec2.hpp>

#include "Component.h"


class Sprite : Component
{
private:
	
public:
	SDL_FRect destRect {};
	SDL_Texture* texture_ {};
	SDL_Renderer* renderer_ {};

	Sprite(const std::string& imagePath, SDL_Renderer* renderer, const glm::vec2& scale);
	Sprite() {
		std::cout << "Sprite constructor called" << std::endl;
	}
	
	~Sprite()
	{
		std::cout << "Sprite destructor called" << std::endl;
	}
	auto& getTexture() const { return texture_; }
	void update();

};
