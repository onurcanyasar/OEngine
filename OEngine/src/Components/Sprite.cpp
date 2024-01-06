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

void Sprite::update() 
{
	SDL_RenderCopyF(renderer_, texture_, nullptr, &destRect);
	
}




