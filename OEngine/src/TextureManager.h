#pragma once
#include <memory>
#include <SDL_render.h>
#include <string>

class TextureManager
{
public:
	static SDL_Texture* loadTexture(const std::string path, SDL_Renderer* renderer);
	

};
