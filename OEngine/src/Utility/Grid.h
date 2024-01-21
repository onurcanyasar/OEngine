#pragma once
#include <iostream>
#include <SDL_render.h>
#include <vector>
#include <glm/vec2.hpp>
class Game;
template <typename T>
class Grid
{
public:
	
	int getNumRows() const { return num_rows_; }
	int getNumCols() const { return num_cols_; }
	int getCellSize() const { return cell_size_; }
	std::vector<std::vector<std::vector<T>>> cells;

	Grid(int num_rows, int num_cols, int cell_size)
	: num_rows_(num_rows), num_cols_(num_cols), cell_size_(cell_size)
	{
		cells.resize(num_rows);
		for (auto& row : cells)
		{
			row.resize(num_cols);
			
		}
		auto a = cells[0][0];
		for (const auto i : a)
		{
			std::cout << i << " ";
		}
	}

	void clear()
	{
		for (auto& row : cells)
		{
			for (auto& col : row)
			{
				col.clear();
			}
		}
	}

	void draw() const
	{
		
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);
		for (int i = 0; i < num_rows_; i++)
		{
			SDL_RenderDrawLine(Game::renderer, 0, i * cell_size_, num_cols_ * cell_size_, i * cell_size_);
			//SDL_RenderPresent(Game::renderer);

			
		}
		for (int i = 0; i < num_cols_; i++)
		{
			SDL_RenderDrawLine(Game::renderer, i * cell_size_, 0, i * cell_size_, num_rows_ * cell_size_);
			//SDL_RenderPresent(Game::renderer);

		}
		SDL_RenderDrawLine(Game::renderer, 0, num_rows_ * cell_size_, num_cols_ * cell_size_, num_rows_ * cell_size_);
		SDL_RenderDrawLine(Game::renderer, num_cols_ * cell_size_, 0, num_cols_ * cell_size_, num_rows_ * cell_size_);
	}
	glm::vec2 getCellCenter(const int row, const int col) const
	{
		return glm::vec2(col * cell_size_ + cell_size_ / 2, row * cell_size_ + cell_size_ / 2);
	}
	glm::vec2 getWorldToCellCenter(const glm::vec2& world_pos) const
	{
		auto [row, col] = getWorldToCellIndex(world_pos);
		return getCellCenter(row, col);
	}
	std::pair<int,int> getWorldToCellIndex(const glm::vec2& world_pos) const
	{
		int row = world_pos.y / cell_size_;
		int col = world_pos.x / cell_size_;
		return std::make_pair(row, col);
	}
	
private: 
	
	int num_rows_{ 0 };
	int num_cols_ { 0 };
	int cell_size_ { 0 };
	



};
