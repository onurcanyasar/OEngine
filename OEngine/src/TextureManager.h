#pragma once
#include <SDL_render.h>
#include <string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	static SDL_Texture* loadTexture(const std::string path, SDL_Renderer* renderer);

};
