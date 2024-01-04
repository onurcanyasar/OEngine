#include "Game.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include "TextureManager.h"


SDL_Renderer* Game::s_renderer{ nullptr }; //forward declaration
SDL_Texture* tex;
SDL_Rect dst;
void Game::init(const std::string& title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{


    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 480;

    initWindowAndRenderer(title, x_pos, y_pos, width, height);

    tex = TextureManager::loadTexture("assets/circle.png", s_renderer);
    dst = { 0, 0, 100, 100 };
}

void Game::handleEvents()
{

    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        is_running_ = false;
        break;
    default:
        break;
    }
}

void Game::update()
{
}

void Game::clean()
{
    
    SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(Game::s_renderer);
	SDL_Quit();
	IMG_Quit();
}


void Game::render()
{
    SDL_SetRenderDrawColor(Game::s_renderer, 255, 255, 255, 255);
    SDL_RenderClear(Game::s_renderer);

    SDL_RenderCopy(s_renderer, tex, nullptr, &dst);

    SDL_RenderPresent(Game::s_renderer);
}

void Game::initWindowAndRenderer(const std::string& title, int x_pos, int y_pos, int width, int height)
{
    window_ = SDL_CreateWindow(title.c_str(), x_pos, y_pos, width, height, SDL_WINDOW_SHOWN);
    if (window_ == nullptr)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create renderer for window
        Game::s_renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (Game::s_renderer == nullptr)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(Game::s_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            is_running_ = true;
            //Initialize PNG loading
            constexpr int img_flags = IMG_INIT_PNG;
            if (!(IMG_Init(img_flags) & img_flags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
            }
        }


    }
}