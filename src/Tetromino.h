#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <queue>

#include "Global.h"


class Tetromino
{
	std::vector<SDL_Point> cellPositions;
	std::vector<SDL_Point> bottomCollisions;
	std::vector<SDL_Point> leftCollisions;
	std::vector<SDL_Point> rightCollisions;

	SDL_Color tetrominoColor;
	SDL_Point tetrominoCenter;
	bool hasLanded;
	bool canRotate;

	int xOffset, yOffset;

	enum tetromino
	{
		IBLOCK,
		JBLOCK,
		LBLOCK,
		OBLOCK,
		SBLOCK,
		TBLOCK,
		ZBLOCK
	};

	enum position
	{
		UP,
		LEFT,
		DOWN,
		RIGHT
	};

	int currentTetromino;
	int currentPosition;

	std::vector<std::vector<SDL_Point>> configuration;


	// All possible Cell Colors
	std::vector<SDL_Color> cell_colors = {
		{0, 240, 240},
		{0, 0, 240},
		{240, 160, 0},
		{240, 240, 0},
		{0, 240, 0},
		{160, 0, 240},
		{240, 0, 0}
	};

	std::vector<std::vector<std::vector<SDL_Point>>> shapeConfigurations = {
		//I-block
		configuration = {
			
			// Up
			cellPositions = {
				{6, 0},
				{5, 0},
				{4, 0},
				{3, 0}
			},

			// Left
			cellPositions = {
				{4, 3},
				{4, 2},
				{4, 1},
				{4, 0}
			},


			// Down
			cellPositions = {
				{6, 0},
				{5, 0},
				{4, 0},
				{3, 0}
			},

			// Right
			cellPositions = {
				{5, 3},
				{5, 2},
				{5, 1},
				{5, 0}
			}
		},

		//J-block
		configuration = {

			// Up
			cellPositions = {
				{6, 1},
				{5, 1},
				{4, 1},
				{4, 0}
			},

			// Left
			cellPositions = {
				{5, 2},
				{4, 2},
				{5, 1},
				{5, 0}
			},

			// Down
			cellPositions = {
				{6, 2},
				{6, 1},
				{5, 1},
				{4, 1}
			},

			// Right
			cellPositions = {
				{5, 2},
				{5, 1},
				{6, 0},
				{5, 0}
			}
		},

		//L-block
		configuration = {

			// Up
			cellPositions = {
				{5, 1},
				{4, 1},
				{3, 1},
				{5, 0}
			},

			// Left
			cellPositions = {
				{4, 2},
				{4, 1},
				{4, 0},
				{3, 0}
			},

			// Down
			cellPositions = {
				{3, 2},
				{5, 1},
				{4, 1},
				{3, 1}
			},

			// Right
			cellPositions = {
				{5, 2},
				{4, 2},
				{4, 1},
				{4, 0}
			}
		},

		// O-Block
		configuration = {
			// Up
			cellPositions = {
				{5, 1},
				{4, 1},
				{5, 0},
				{4, 0}
			},

			// Left
			cellPositions = {
				{5, 1},
				{4, 1},
				{5, 0},
				{4, 0}
			},

			// Down
			cellPositions = {
				{5, 1},
				{4, 1},
				{5, 0},
				{4, 0}
			},

			// Right
			cellPositions = {
				{5, 1},
				{4, 1},
				{5, 0},
				{4, 0}
			}

		},

		// S-Block
		configuration = {
			// Up
			cellPositions = {
				{4, 1},
				{3, 1},
				{5, 0},
				{4, 0}
			},

			// Left
			cellPositions = {
				{4, 2},
				{4, 1},
				{3, 1},
				{3, 0}
			},

			// Down
			cellPositions = {
				{4, 2},
				{3, 2},
				{5, 1},
				{4, 1}
			},

			// Right
			cellPositions = {
				{5, 2},
				{5, 1},
				{4, 1},
				{4, 0}
			}

		},

		// T-Block
		configuration = {
			// Up
			cellPositions = {
				{5, 1},
				{4, 1},
				{3, 1},
				{4, 0}
			},

			// Left
			cellPositions = {
				{4, 2},
				{4, 1},
				{3, 1},
				{4, 0}
			},

			// Down
			cellPositions = {
				{4, 2},
				{5, 1},
				{4, 1},
				{3, 1}
			},

			// Right
			cellPositions = {
				{4, 2},
				{5, 1},
				{4, 1},
				{4, 0}
			}

		},


		// Z-Block
		configuration = {
			// Up
			cellPositions = {
				{6, 1},
				{5, 1},
				{5, 0},
				{4, 0}
			},

			// Left
			cellPositions = {
				{4, 2},
				{5, 1},
				{4, 1},
				{5, 0}
			},

			// Down
			cellPositions = {
				{6, 2},
				{5, 2},
				{5, 1},
				{4, 1}
			},

			// Right
			cellPositions = {
				{5, 2},
				{6, 1},
				{5, 1},
				{6, 0}
			}

		}






	};


	std::vector<std::vector<SDL_Point>> shapes = {

		// I-block
		cellPositions = {
			{6, 0},
			{5, 0},
			{4, 0},
			{3, 0}
		},

		// J-block
		cellPositions = {
			{6, 1},
			{5, 1},
			{4, 1},
			{4, 0}
		},

		// L-block
		cellPositions = {
			{5, 1},
			{4, 1},
			{3, 1},
			{5, 0}
		},

		// O-block
		cellPositions = {
			{5, 1},
			{4, 1},
			{5, 0},
			{4, 0}
		},

		// S-block
		cellPositions = {
			{4, 1},
			{3, 1},
			{5, 0},
			{4, 0}
		},

		// T-block
		cellPositions = {
			{5, 1},
			{4, 1},
			{3, 1},
			{4, 0}
		},

		// Z-block
		cellPositions = {
			{6, 1},
			{5, 1},
			{5, 0},
			{4, 0}
		}

	};

	std::vector<SDL_Point> centers = {
		// I-block
		{0, 0},

		// J-block
		{0, 0},

		// L-block
		{0, 0},
		// O-block
		{0, 0},

		// S-block
		{0, 0},

		// T-block
		{4, 1},

		// Z-block
		{0, 0}
	};

public:
	Tetromino();
	void calculateCollisionCells();
	void spawn(std::vector<std::vector<unsigned char>>& matrix);
	void moveDown(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>> &colors, const SDL_Color& backgroundColor);
	void moveRight(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor);
	void moveLeft(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor);
	void update_matrix(std::vector<std::vector<unsigned char>>& matrix);
	bool isLanded() { return hasLanded; }
	SDL_Color getColor() { return tetrominoColor; }

	void rotateLeft(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor);
	void rotateRight(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor);

	int getBlockType() { return currentTetromino; }

	void removeTetrominoFromGrid(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor);
	void fastDrop(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor);
//	std::vector<SDL_Point> pieces;
// 
//
//public:
//	Tetromino(unsigned char shape);
//
//	bool move_down(const std::vector<std::vector<unsigned char>>& matrix);
//
//	void reset(unsigned char shape);
//	void update_matrix(std::vector<std::vector<unsigned char>>& matrix);
//
//	std::vector<SDL_Point> get_pieces();
};

