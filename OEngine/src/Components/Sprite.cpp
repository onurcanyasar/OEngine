#include "Sprite.h"

#include <iostream>

#include "../TextureManager.h"

Sprite::Sprite(const std::string& imagePath, SDL_Renderer* renderer, const glm::vec2& scale)
{
	renderer_ = renderer;
	texture_ = TextureManager::loadTexture(imagePath, renderer_);
	destRect = { 0, 0, scale.x, scale.y };
	std::cout << "sprite tex loaded" << std::endl;
}

Sprite::Sprite()
{
	std::cout << "Sprite ctor called" << std::endl;
}

Sprite::~Sprite()
{

	SDL_DestroyTexture(texture_);
	std::cout << "Sprite dtor called" << std::endl;
}

Sprite::Sprite(Sprite&& other) noexcept
{
	std::cout << "Sprite move ctor called" << std::endl;
	
	texture_ = other.texture_;
	destRect = other.destRect;
	renderer_ = other.renderer_;
	other.texture_ = nullptr;

}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
	std::cout << "Sprite move assignment operator called" << std::endl;
	if (this != &other)
	{
		texture_ = other.texture_;
		destRect = other.destRect;
		renderer_ = other.renderer_;
		other.texture_ = nullptr;
	}
	return *this;
}






