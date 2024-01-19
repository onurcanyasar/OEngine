#include "Game.h"

#include <iostream>
#include <random>

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>


#include "Components/Collider2D.h"
#include "Entity/EntityMemoryPool.h"
#include "Entity/EntityManager.h"

#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Systems/ColliderSystem.h"

#include "Systems/MoveSystem.h"
#include "Systems/SpriteSystem.h"

SDL_Renderer* Game::renderer{ nullptr };
const int pool_size = 101;

std::shared_ptr<EntityMemoryPool> memory_pool = std::make_shared<EntityMemoryPool>(pool_size);
EntityManager entity_manager(memory_pool.get());
Entity player;

SpriteSystem sprite_system(memory_pool.get());
MoveSystem move_system(memory_pool.get());
ColliderSystem collider_system(memory_pool);
std::random_device rd;  // Random device engine
std::mt19937 rng(rd()); // Initialize Mersennes' twister

void createRedSquareEntity();
void Game::init(const std::string& title, int x_pos, int y_pos, int width, int height)
{

    initWindowAndRenderer(title, x_pos, y_pos, width, height);


    memory_pool->registerComponentType<Sprite>();
    memory_pool->registerComponentType<Transform>();
    memory_pool->registerComponentType<Velocity>();
    memory_pool->registerComponentType<Collider2D>();

    for (int i = 0; i < pool_size - 1; i++)
	{
		createRedSquareEntity();
	}
    /*player = entity_manager.createEntity();
    memory_pool->addComponent<Sprite>(player.id, "assets/red_square.png", Game::renderer, glm::vec2(50, 50));
    memory_pool->addComponent<Transform>(player.id);
    SDL_FRect rect = { 0,0,50,50};
    memory_pool->addComponent<Collider2D>(player.id, 50, 50);
    std::cout << "initialization finished\n";

    Entity e = entity_manager.createEntity();
    memory_pool->addComponent<Sprite>(e.id, "assets/red_square.png", Game::renderer, glm::vec2(50, 50));
    memory_pool->addComponent<Transform>(e.id);
    memory_pool->addComponent<Collider2D>(e.id, 50, 50);*/
    

}
void createRedSquareEntity()
{
    Entity e = entity_manager.createEntity();
    constexpr float scale = 12;
    memory_pool->addComponent<Sprite>(e.id, "assets/red_square.png", Game::renderer, glm::vec2(scale, scale));
    memory_pool->addComponent<Transform>(e.id);
    memory_pool->addComponent<Collider2D>(e.id, scale, scale);

    std::uniform_real_distribution<float> random_rot_dist(-5, 5); 
    std::uniform_real_distribution<float> random_dist(-4.0, 4.0);
    
    
    float random_x = random_dist(rng);
    
    
    float random_y = random_dist(rng);
    float random_rotation = random_rot_dist(rng);
    
   
    std::cout << "random x: " << random_x << std::endl;
    std::cout << "random y: " << random_y << std::endl;
    memory_pool->addComponent<Velocity>(e.id, random_x,random_y,random_rotation);
    float x = rand() % 800;
    float y = rand() % 640;
    float rot = rand() % 360;
    
    memory_pool->getComponent<Transform>(e.id).position = glm::vec2(x, y);
    memory_pool->getComponent<Transform>(e.id).rotation = rot;


}
int x_mouse{};
int y_mouse{};

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type)
    {
	    case SDL_QUIT:
	        is_running_ = false;
	        break;
        case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&x_mouse, &y_mouse);
			std::cout << "Mouse clicked at: " << x_mouse << ", " << y_mouse << std::endl;
			break;
	    default:
	        break;
    }
}

int i = 50;
void Game::update()
{

    
    entity_manager.update();
    std::cout << memory_pool->entity_set << std::endl;
    /*if (i < 70)
    {
	    entity_manager.removeEntity(i);
        i++;
    }*/
    /*auto& trans = memory_pool->getComponent<Transform>(player.id);
    trans.position.x = static_cast<float>(x_mouse);
    trans.position.y = static_cast<float>(y_mouse);
    */
    move_system.update();
    collider_system.update();

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