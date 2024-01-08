#include "Game.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "IComponentPool.h"
#include "TextureManager.h"

#include "Entity/EntityMemoryPool.h"
#include "Entity/EntityManager.h"

#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Systems/MoveSystem.h"
#include "Systems/SpriteSystem.h"

SDL_Renderer* Game::s_renderer{ nullptr }; 
SDL_Texture* tex;
SDL_Texture* tex2;
SDL_Rect dst;
EntityMemoryPool memoryPool(5000);
EntityManager entityManager(&memoryPool);
std::shared_ptr<ComponentPool<Sprite>> spritePool;
SpriteSystem spriteSystem(&memoryPool);
MoveSystem moveSystem(&memoryPool);

void createRedSquareEntity();
void Game::init(const std::string& title, int x_pos, int y_pos, int width, int height)
{


    
    
    initWindowAndRenderer(title, x_pos, y_pos, width, height);

    tex = TextureManager::loadTexture("assets/circle.png", s_renderer);
    tex2 = TextureManager::loadTexture("assets/loaded.png", s_renderer);
    dst = { 0, 0, 100, 100 };


    memoryPool.registerComponentType<Sprite>();
    memoryPool.registerComponentType<Transform>();
    memoryPool.registerComponentType<Velocity>();

    for (int i = 0; i < 5000; i++)
	{
		createRedSquareEntity();
	}

    std::cout << "init finished";

}
void createRedSquareEntity()
{
    Entity e = entityManager.addEntity();
    memoryPool.addComponent<Sprite>(e.id, "assets/red_square.png", Game::s_renderer, glm::vec2(12, 12));
    memoryPool.addComponent<Transform>(e.id);
    float random_rotation = static_cast<float>(rand() % 50 - 25);
    float random_x = static_cast<float>(rand() % 10 - 5);
    float random_y = static_cast<float>(rand() % 5 + 1);
    memoryPool.addComponent<Velocity>(e.id, random_x,random_y,random_rotation);
    float x = rand() % 800;
    float y = rand() % 640;
    float rot = rand() % 360;
    memoryPool.getComponent<Transform>(e.id).position = glm::vec2(x, y);
    memoryPool.getComponent<Transform>(e.id).rotation = rot;


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

int i = 0;
int id = 0;
void Game::update()
{

    /*entityManager.update();
    if (i % 5 == 0 && id < 245)
    {
        entityManager.removeEntity(id);
        id++;
    }

    i++;*/
    moveSystem.update();
    
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

    //SDL_RenderCopy(s_renderer, tex, nullptr, &dst);
    spriteSystem.render();


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