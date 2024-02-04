#include "Sprite.hpp"

#include <iostream>

#include "../TextureManager.h"

Sprite::Sprite(const std::string& imagePath, SDL_Renderer* renderer, const glm::vec2& scale)
{
	renderer_ = renderer;
	texture_ = TextureManager::loadTexture(imagePath, renderer_);
	destRect = { 0, 0, scale.x, scale.y };
}



Sprite::~Sprite()
{

	SDL_DestroyTexture(texture_);
}

Sprite::Sprite(Sprite&& other) noexcept
{
	
	texture_ = other.texture_;
	destRect = other.destRect;
	renderer_ = other.renderer_;
	other.texture_ = nullptr;

}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
	if (this != &other)
	{
		texture_ = other.texture_;
		destRect = other.destRect;
		renderer_ = other.renderer_;
		other.texture_ = nullptr;
	}
	return *this;
}






