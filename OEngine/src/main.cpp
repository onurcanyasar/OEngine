#include <chrono>
#include <ostream>
#include <SDL_timer.h>

#include "Game.h"
#include <glm/glm.hpp>



int main() {

	
		Game game;
		constexpr int FPS = 30;
		constexpr int frameDelay = 1000 / FPS;

		const auto resolution = std::make_pair<int, int>(800, 640);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		Uint32 frameStart;
		int frameTime;

		game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.first, resolution.second);


		while (game.isRunning()) {

			frameStart = SDL_GetTicks();


			game.handleEvents();

			game.update();

			game.render();

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}



		}

		game.clean();
		//delete game;
	

	


	return 0;




}
