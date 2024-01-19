#include "CircleRenderSystem.h"


void CircleRenderSystem::update()
{
    for(const auto i : entity_memory_pool_->entity_set.dense_vec)
    {
	    

        const std::size_t entity_id = entity_memory_pool_->entity_set.dense_vec[i];
        if (entity_id == 0) continue;
		const auto& circle = entity_memory_pool_->getComponent<Circle>(entity_id);
		const auto& transform = entity_memory_pool_->getComponent<Transform>(entity_id);

		SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
        SDL_RenderDrawPointF(Game::renderer, transform.position.x, transform.position.y);
        //std::cout << "render pos circle" << transform.position.x << " " << transform.position.y << std::endl;
		drawCircle(Game::renderer, transform.position.x, transform.position.y, circle.radius);
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
