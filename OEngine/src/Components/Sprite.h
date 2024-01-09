#pragma once
#include <iostream>
#include <SDL_render.h>
#include <glm/vec2.hpp>


struct Sprite 
{

SDL_FRect destRect {};
SDL_Texture* texture_ {};
SDL_Renderer* renderer_ {};

Sprite(const std::string& imagePath, SDL_Renderer* renderer, const glm::vec2& scale);
Sprite();
~Sprite();
Sprite(Sprite&& other) noexcept;
Sprite& operator=(Sprite&& other) noexcept;
Sprite(const Sprite& other) = delete;
Sprite& operator=(const Sprite& other) = delete;
	

};
