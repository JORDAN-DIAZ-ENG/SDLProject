#pragma once

#include <SDL.h>

// Tetris has a grid of ten columns and 20 rows
#define COLUMNS 10
#define ROWS 20

// The grid will have cells that have a size of 8x8
#define CELL_SIZE 8

// The actual pixel size is pretty small, upscale by a factor of 4
#define RESIZE 4

inline bool operator==(SDL_Point const& a, SDL_Point const& b)
{
	return a.x == b.x && a.y == b.y;
}

inline bool operator!=(SDL_Point const& a, SDL_Point const& b)
{
	return !(a == b);
}
