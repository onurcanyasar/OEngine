#include "SpriteSystem.h"


void SpriteSystem::render() const
{

	for (std::size_t id = 0; id < entity_memory_pool_->active_vector.size(); id++)
	{
		if (entity_memory_pool_->active_vector[id]) //TODO: gonna change this, this is inefficient. Start from the last active entity and go backwards.
		{

			auto& sprite = entity_memory_pool_->getComponent<Sprite>(id);
			const auto& transform = entity_memory_pool_->getComponent<Transform>(id);

			sprite.destRect.x = transform.position.x;
			sprite.destRect.y = transform.position.y;

			constexpr SDL_RendererFlip flip = SDL_FLIP_NONE;
			
			SDL_RenderCopyExF(sprite.renderer_, sprite.texture_, nullptr, &sprite.destRect, transform.rotation, nullptr, flip);

			
		}
	}
}
