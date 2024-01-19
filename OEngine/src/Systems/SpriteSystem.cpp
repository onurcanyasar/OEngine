#include "SpriteSystem.h"


void SpriteSystem::render() const
{

	for (std::size_t id = 0; id < entity_memory_pool_->active_vector.size(); id++)
	{
		if (entity_memory_pool_->active_vector[id]) //TODO: gonna change this, this is inefficient. Start from the last active entity and go backwards.
		{

			auto& sprite = entity_memory_pool_->getComponent<Sprite>(id);
			const auto& transform = entity_memory_pool_->getComponent<Transform>(id);

			sprite.destRect.x = transform.position.x - sprite.destRect.w / 2;
			sprite.destRect.y = transform.position.y - sprite.destRect.h / 2;
			//std::cout << "render pos sprite" << transform.position.x << " " << transform.position.y << std::endl;
			constexpr SDL_RendererFlip flip = SDL_FLIP_NONE;
			
			//SDL_RenderCopyExF(sprite.renderer_, sprite.texture_, nullptr, &sprite.destRect, transform.rotation, nullptr, flip);
			SDL_Rect destRect = {
				static_cast<int>(sprite.destRect.x),
				static_cast<int>(sprite.destRect.y),
				static_cast<int>(sprite.destRect.w),
				static_cast<int>(sprite.destRect.h)
			};
			SDL_RenderCopyEx(sprite.renderer_, sprite.texture_, nullptr, &destRect, transform.rotation, nullptr, flip);

			
		}
	}
}
