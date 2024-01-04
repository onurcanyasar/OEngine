#include <chrono>
#include <ostream>
#include <SDL_timer.h>

#include "Game.h"
#include <glm/glm.hpp>



int main() {

	
		Game game;
		constexpr int FPS = 100;
		constexpr int frameDelay = 1000 / FPS;

		const auto resolution = std::make_pair<int, int>(800, 640);
		const bool isFullscreen = false;

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		Uint32 last_tick = 0;
		Uint32 tick_time = 0;
		double deltaTime = 0;


		game.init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.first, resolution.second, isFullscreen);


		while (game.isRunning()) {

			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			tick_time = SDL_GetTicks();
			deltaTime = (tick_time - last_tick) / 1000.0; //deltaTime in milliseconds
			last_tick = tick_time;

			game.handleEvents();

			game.update();

			game.render();

			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			




		}

		game.clean();
		//delete game;
	

	


	return 0;




}
