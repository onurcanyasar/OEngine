#include "Game.h"

#include <iostream>
#include <random>

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>


#include "Components/RectCollider.h"
#include "Entity/EntityMemoryPool.h"
#include "Entity/EntityManager.h"

#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Systems/CircleCollisionSystem.h"
#include "Systems/CircleRenderSystem.h"
#include "Systems/ColliderSystem.h"
#include "Systems/CollisionGridSystem.h"
#include "Utility/Grid.h"
#include "Systems/MoveSystem.h"
#include "Systems/SpriteSystem.h"

SDL_Renderer* Game::renderer{ nullptr };
constexpr int pool_size = 501;

EntityMemoryPool memory_pool(pool_size);
EntityManager entity_manager(&memory_pool);
Entity player;

SpriteSystem sprite_system(&memory_pool);
MoveSystem move_system(&memory_pool);
ColliderSystem collider_system(&memory_pool);
CircleRenderSystem circle_render_system(&memory_pool);
CircleCollisionSystem circle_collision_system(&memory_pool);
Grid<std::size_t> grid(15, 20, 40);
CollisionGridSystem collision_grid_system(&memory_pool, &grid);

std::random_device rd;  // Random device engine
std::mt19937 rng(rd()); // Initialize Mersennes' twister

void createCircleOnRandomPosition();
void Game::init(const std::string& title, int x_pos, int y_pos, int width, int height)
{
    initWindowAndRenderer(title, x_pos, y_pos, width, height);

    memory_pool.registerComponentType<Sprite>();
    memory_pool.registerComponentType<Transform>();
    memory_pool.registerComponentType<Velocity>();
    memory_pool.registerComponentType<RectCollider>();
    memory_pool.registerComponentType<Circle>();
    memory_pool.registerComponentType<CircleCollider>();

    for (int i = 0; i < pool_size - 1; i++)
	{
		createCircleOnRandomPosition();
	}
    
    
    

}
void createCircleOnRandomPosition()
{
    Entity e = entity_manager.createEntity();

    std::uniform_real_distribution<float> random_scale_dist(1, 4);
    const float random_scale = random_scale_dist(rng);
	const float scale = 5 * random_scale;
	const float radius = 2.5 * random_scale;
    
    memory_pool.addComponent<Sprite>(e, "assets/red_circle.png", Game::renderer, glm::vec2(scale, scale));
    sprite_system.addEntity(e);

    memory_pool.addComponent<Transform>(e);

    memory_pool.addComponent<CircleCollider>(e, radius);
    circle_collision_system.addEntity(e);

    memory_pool.addComponent<Circle>(e, radius);
    circle_render_system.addEntity(e);
    collision_grid_system.addEntity(e);


    float velocity_range{ 100 };
    std::uniform_real_distribution<float> random_rot_dist(-15, 150); 
    std::uniform_real_distribution<float> random_dist(-velocity_range, velocity_range);
    
    
    float random_x_vel = random_dist(rng);
    float random_y_vel = random_dist(rng);
   

    float random_rotation = random_rot_dist(rng);
    random_rotation = 0;
   
    
    memory_pool.addComponent<Velocity>(e, random_x_vel,random_y_vel,random_rotation);
    move_system.addEntity(e);

    float x = rand() % 800;
    float y = rand() % 640;
    float rot = rand() % 360;
    
    memory_pool.getComponent<Transform>(e).position = glm::vec2(x, y);
    memory_pool.getComponent<Transform>(e).rotation = 0;


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

int i = 1;
int frame = 1;
void Game::update(float delta_time)
{
    entity_manager.update();
    //std::cout << memory_pool->entity_set << std::endl;
    
    /*if (frame % 200 == 0 && i < pool_size)
    {
	    entity_manager.removeEntity(i);
        collision_grid_system.removeEntity(i);
        circle_collision_system.removeEntity(i);
        sprite_system.removeEntity(i);
        circle_render_system.removeEntity(i);

        i++;
    }
    frame++;*/
    /*auto& trans = memory_pool->getComponent<Transform>(1);
    trans.position.x = static_cast<float>(x_mouse);
    trans.position.y = static_cast<float>(y_mouse);*/

    move_system.updateDeltaTime(delta_time);
    move_system.update();
    
    //circle_collision_system.update();
    collision_grid_system.update();

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

    
    sprite_system.update();
    //collision_grid_system.grid_->draw();

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