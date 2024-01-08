#include "SpriteSystem.h"


void SpriteSystem::render()
{

	for (std::size_t id = 0; id < entity_memory_pool_->active_vector_.size(); id++)
	{
		if (entity_memory_pool_->active_vector_[id])
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
