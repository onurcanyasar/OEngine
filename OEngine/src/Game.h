#pragma once
#include <SDL_render.h>
#include <string>

class Game
{

public:
	static SDL_Renderer* renderer;
	void init(const std::string& title, int x_pos, int y_pos, int width, int height);
	void handleEvents();
	void update(float delta_time);
	void render();
	void clean();
	bool isRunning() const { return is_running_; }
	void finishGame() { is_running_ = false; }
	Game() = default;
	~Game() = default;
private:
	bool is_running_{ false };
	SDL_Window* window_{ nullptr };
	void initWindowAndRenderer(const std::string& title, int x_pos, int y_pos, int width, int height);
};

