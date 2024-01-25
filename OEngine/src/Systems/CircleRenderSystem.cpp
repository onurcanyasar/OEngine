#include "CircleRenderSystem.h"


void CircleRenderSystem::update()
{
    for (std::size_t i = 0; i < entities_.dense_end; i++)
    {
	    

        const std::size_t entity_id = entity_memory_pool_->entity_set.dense_vec[i];
        if (entity_id == 0) continue;
		const auto& circle = entity_memory_pool_->getComponent<Circle>(entity_id);
		const auto& transform = entity_memory_pool_->getComponent<Transform>(entity_id);
        
		SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
        SDL_RenderDrawPointF(Game::renderer, transform.position.x, transform.position.y);
        //std::cout << "render pos circle" << transform.position.x << " " << transform.position.y << std::endl;
		drawCircleCosSin(Game::renderer, transform.position.x, transform.position.y, circle.radius);
	}
}

void CircleRenderSystem::drawCircle(SDL_Renderer* renderer, float center_x, float center_y, float radius)
{
    const float diameter = (radius * 2);

    float x = (radius - 1);
    float y = 0;
    float tx = 1;
    float ty = 1;
    float error = (tx - diameter);
    
    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPointF(renderer, center_x + x, center_y - y);
        SDL_RenderDrawPointF(renderer, center_x + x, center_y + y);
        SDL_RenderDrawPointF(renderer, center_x - x, center_y - y);
        SDL_RenderDrawPointF(renderer, center_x - x, center_y + y);
        SDL_RenderDrawPointF(renderer, center_x + y, center_y - x);
        SDL_RenderDrawPointF(renderer, center_x + y, center_y + x);
        SDL_RenderDrawPointF(renderer, center_x - y, center_y - x);
        SDL_RenderDrawPointF(renderer, center_x - y, center_y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void CircleRenderSystem::drawCircleCosSin(SDL_Renderer* renderer, float center_x, float center_y, float radius)
{
	constexpr float pi = 3.14159265358979323846264338327950288419716939937510f;
	constexpr float pi_half = pi / 2.0; 

    constexpr int precision = 27; 
    float theta = 0;     
    
    //starting point
    float x = radius * cos(theta);//start point
    float y = radius * sin(theta);//start point
    float x1 = x;
    float y1 = y;

    //repeat until theta >= 90;
	constexpr float step = pi_half / static_cast<float>(precision); // amount to add to theta each time (degrees)
    for (theta = step; theta <= pi_half; theta += step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = radius * cosf(theta); //new point (+.5 is a quick rounding method)
        y1 = radius * sinf(theta); //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if ((x != x1) || (y != y1))//only draw if coordinate changed
        {
            SDL_RenderDrawLineF(renderer, center_x + x, center_y - y, center_x + x1, center_y - y1);//quadrant TR
            SDL_RenderDrawLineF(renderer, center_x - x, center_y - y, center_x - x1, center_y - y1);//quadrant TL
            SDL_RenderDrawLineF(renderer, center_x - x, center_y + y, center_x - x1, center_y + y1);//quadrant BL
            SDL_RenderDrawLineF(renderer, center_x + x, center_y + y, center_x + x1, center_y + y1);//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if (x != 0)
    {
        x = 0;
        SDL_RenderDrawLineF(renderer, center_x + x, center_y - y, center_x + x1, center_y - y1);//quadrant TR
        SDL_RenderDrawLineF(renderer, center_x - x, center_y - y, center_x - x1, center_y - y1);//quadrant TL
        SDL_RenderDrawLineF(renderer, center_x - x, center_y + y, center_x - x1, center_y + y1);//quadrant BL
        SDL_RenderDrawLineF(renderer, center_x + x, center_y + y, center_x + x1, center_y + y1);//quadrant BR
    }

    
}
