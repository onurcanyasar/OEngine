#include "Game.h"

#include <iostream>
#include <random>

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>


#include "Entity/EntityMemoryPool.h"
#include "Entity/EntityManager.h"

#include "Components/Transform.h"
#include "Components/Sprite.h"

#include "Systems/MoveSystem.h"
#include "Systems/SpriteSystem.h"

SDL_Renderer* Game::renderer{ nullptr };
const int pool_size = 500;

EntityMemoryPool memory_pool(pool_size);
EntityManager entity_manager(&memory_pool);

SpriteSystem sprite_system(&memory_pool);
MoveSystem move_system(&memory_pool);

std::random_device rd;  // Random device engine
std::mt19937 rng(rd()); // Initialize Mersennes' twister

void createRedSquareEntity();
void Game::init(const std::string& title, int x_pos, int y_pos, int width, int height)
{

    initWindowAndRenderer(title, x_pos, y_pos, width, height);


    memory_pool.registerComponentType<Sprite>();
    memory_pool.registerComponentType<Transform>();
    memory_pool.registerComponentType<Velocity>();

    for (int i = 0; i < pool_size; i++)
	{
		createRedSquareEntity();
	}
    std::cout << "init finished";
    

}
void createRedSquareEntity()
{
    Entity e = entity_manager.createEntity();
    memory_pool.addComponent<Sprite>(e.id, "assets/red_square.png", Game::renderer, glm::vec2(12, 12));
    memory_pool.addComponent<Transform>(e.id);
    std::uniform_real_distribution<float> random_rot_dist(-5, 5); 
    std::uniform_real_distribution<float> random_dist(-2.0, 2.0); 
    float random_x = random_dist(rng);
    float random_y = random_dist(rng);
    float random_rotation = random_rot_dist(rng);

   
    
    memory_pool.addComponent<Velocity>(e.id, random_x,random_y,random_rotation);
    float x = rand() % 800;
    float y = rand() % 640;
    float rot = rand() % 360;
    memory_pool.getComponent<Transform>(e.id).position = glm::vec2(x, y);
    memory_pool.getComponent<Transform>(e.id).rotation = rot;


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

    entity_manager.update();
    move_system.update();

}

void Game::clean()
{
    
    SDL_DestroyWindow(window_);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	IMG_Quit();
}


void Game::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
    SDL_RenderClear(Game::renderer);

    //SDL_RenderCopy(renderer, tex, nullptr, &dst);
    sprite_system.render();


    SDL_RenderPresent(Game::renderer);
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
        Game::renderer = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (Game::renderer == nullptr)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(Game::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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