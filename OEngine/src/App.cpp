#include "App.h"
#include <chrono>
#include <ostream>
#include <SDL_timer.h>

#include "Game.h"
#include <glm/glm.hpp>



void App::run() {


	Game game;
	constexpr int FPS = 120;
	constexpr int frameDelay = 1000 / FPS;

	const auto resolution = std::make_pair<int, int>(801, 601);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	uint32_t millisecsPreviousFrame{ 0 };
	
	int frameTime;

	game.init("OEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resolution.first, resolution.second);



	while (game.isRunning()) {


		auto timeToWait = frameDelay - (SDL_GetTicks() - millisecsPreviousFrame);
		if (timeToWait > 0 && timeToWait <= frameDelay)
			SDL_Delay(timeToWait);

		// difference in ticks since the last frame, in seconds
		float deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;

		// Store the previous frame time
		millisecsPreviousFrame = SDL_GetTicks();


		game.handleEvents();

		game.update(deltaTime);

		game.render();



	}

	game.clean();





}
