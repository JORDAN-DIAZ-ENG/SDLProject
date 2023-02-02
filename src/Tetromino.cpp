#include "Tetromino.h"
#include <algorithm>
#include <unordered_set>
#include <ctime>
#include "Global.h"


Tetromino::Tetromino()
{
	hasLanded = false;
	canRotate = true;
	
	srand(time(0));
	int randNum = rand() % 7;

	xOffset = 0;
	yOffset = 0;

	currentPosition = position::UP;
	currentTetromino = randNum;

	//cellPositions = shapes.at(0);

	cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);

	//if (currentTetromino == 1)
	//	std::cout << "yes: " << tetromino::JBLOCK + 1 << "\n";

	tetrominoColor = cell_colors[randNum];
	//tetrominoCenter = centers.at(5);

	calculateCollisionCells();


}

void Tetromino::spawn(std::vector<std::vector<unsigned char>>& matrix)
{
	for (const SDL_Point position : cellPositions)
	{
		matrix[position.x][position.y] = 1 - matrix[position.x][position.y];
	}
}

void Tetromino::update_matrix(std::vector<std::vector<unsigned char>>& matrix)
{
	for (const SDL_Point position : cellPositions)
	{
		matrix[position.x][position.y] = 1 - matrix[position.x][position.y];
	}
}

void Tetromino::moveRight(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor)
{
	int xPos, yPos;

	calculateCollisionCells();

	for (const SDL_Point& collisionCell : rightCollisions)
	{
	
		if (collisionCell.x > 9 || matrix[collisionCell.x][collisionCell.y] != NULL)
		{
			return;
		}
	}

	xOffset += 1;

	// Move
	for (const SDL_Point& position : cellPositions)
	{
		// Old Positions
		xPos = position.x + xOffset - 1;
		yPos = position.y + yOffset;

		// Remove Color from cell at the Old Position
		matrix[xPos][yPos] = NULL;
		colors[xPos][yPos] = backgroundColor;

		// Apply the new Offset
		xPos = position.x + xOffset;

		// Update the matricies to represent the change
		matrix[xPos][yPos] = 1 - matrix[xPos][yPos];
		colors[xPos][yPos] = tetrominoColor;

	}
}

void Tetromino::moveLeft(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor)
{
	int xPos, yPos;

	calculateCollisionCells();

	for (const SDL_Point& collisionCell : leftCollisions)
	{
		if (collisionCell.x < 0 || matrix[collisionCell.x][collisionCell.y] != NULL)
		{
			return;
		}
	}

	xOffset -= 1;

	// Move
	for (int i = cellPositions.size() - 1; i > -1; i--)
	{
		//Old Positions
		xPos = cellPositions[i].x + xOffset + 1;
		yPos = cellPositions[i].y + yOffset;

		// Remove Color from cell at the Old Position
		matrix[xPos][yPos] = NULL;
		colors[xPos][yPos] = backgroundColor;

		// Apply the new Offset
		xPos = cellPositions[i].x + xOffset;

		// Update the matricies to represent the change
		matrix[xPos][yPos] = 1 - matrix[cellPositions[i].x][cellPositions[i].y];
		colors[xPos][yPos] = tetrominoColor;

	}



}

void Tetromino::moveDown(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor)
{

	int xPos, yPos;
	if (!hasLanded)
	{

		calculateCollisionCells();


		for (SDL_Point& collisionCell : bottomCollisions)
		{
			if (collisionCell.y > 19 || matrix[collisionCell.x][collisionCell.y] != NULL)
			{
				hasLanded = true;
				return;
			}
		}

		yOffset += 1;
		// Move
		for (SDL_Point& position : cellPositions)
		{
			// Old Position
			xPos = position.x + xOffset;
			yPos = position.y + yOffset - 1;

			// Remove Color from cell at the Old Position
			matrix[xPos][yPos] = NULL;
			colors[xPos][yPos] = backgroundColor;

			// Apply the new Offset
			yPos = position.y + yOffset;

			// Update the matricies to represent the change
			matrix[xPos][yPos] = 1 - matrix[xPos][yPos];
			colors[xPos][yPos] = tetrominoColor;
		}



	}
}



void Tetromino::calculateCollisionCells()
{
	rightCollisions.clear();
	leftCollisions.clear();
	bottomCollisions.clear();

	for (const SDL_Point position : cellPositions)
	{
		SDL_Point right = { position.x + xOffset + 1, position.y + yOffset };
		SDL_Point left = { position.x + xOffset - 1, position.y + yOffset };
		SDL_Point below = { position.x + xOffset, position.y + yOffset + 1 };

		SDL_Point cellAt0, cellAt1, cellAt2, cellAt3;

		cellAt0.x = cellPositions.at(0).x + xOffset;
		cellAt0.y = cellPositions.at(0).y + yOffset;

		cellAt1.x = cellPositions.at(1).x + xOffset;
		cellAt1.y = cellPositions.at(1).y + yOffset;

		cellAt2.x = cellPositions.at(2).x + xOffset;
		cellAt2.y = cellPositions.at(2).y + yOffset;

		cellAt3.x = cellPositions.at(3).x + xOffset;
		cellAt3.y = cellPositions.at(3).y + yOffset;

		if (right != cellAt0 && right != cellAt1 && right != cellAt2 && right != cellAt3)
			rightCollisions.push_back(right);

		if (left != cellAt0 && left != cellAt1 && left != cellAt2 && left != cellAt3)
			leftCollisions.push_back(left);

		if (below != cellAt0 && below != cellAt1 && below != cellAt2 && below != cellAt3)
			bottomCollisions.push_back(below);
	}


}

void Tetromino::rotateLeft(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor)
{
	if (!canRotate)
		return;



	int xPos, yPos;
		
	// Delete Tetromino from grid
	for (SDL_Point& position : cellPositions)
	{
		// Old Position
		xPos = position.x + xOffset;
		yPos = position.y + yOffset;

		// Remove Color from cell at the Old Position
		matrix[xPos][yPos] = NULL;
		colors[xPos][yPos] = backgroundColor;

	}

	// Apply rotation
	if (currentPosition == position::RIGHT)
	{
		currentPosition = position::UP;
		cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
	}
	else
	{
		currentPosition = currentPosition + 1;
		cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
	}

	for (int i = 0; i < cellPositions.size(); i++)
	{
		xPos = cellPositions[i].x + xOffset;
		yPos = cellPositions[i].y + yOffset;


		if (xPos > 9 || xPos < 0)
		{
			if (currentPosition == position::UP)
			{
				currentPosition = position::RIGHT;
				cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
			}
			else
			{
				currentPosition = currentPosition - 1;
				cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
			}
			break;
		}



		if (matrix[xPos][yPos] != NULL)
		{
			SDL_Point pos0;
			pos0.x = cellPositions[0].x + xOffset;
			pos0.y = cellPositions[0].y + yOffset;
			SDL_Point pos1;
			pos1.x = cellPositions[1].x + xOffset;
			pos1.y = cellPositions[1].y + yOffset;
			SDL_Point pos2;
			pos2.x = cellPositions[2].x + xOffset;
			pos2.y = cellPositions[2].y + yOffset;
			SDL_Point pos3;
			pos3.x = cellPositions[3].x + xOffset;
			pos3.y = cellPositions[3].y + yOffset;

			SDL_Point checkLeft = {xPos - 1, yPos};
			SDL_Point checkRight = {xPos + 1, yPos};
			SDL_Point checkUp = {xPos, yPos - 1};


			// Check Up
			if (yPos > -1 && matrix[xPos][yPos - 1] == NULL && checkUp != pos0 && checkUp != pos1 && checkUp != pos2 && checkUp != pos3)
			{
				yOffset--;
				i = 0;
			}
			// Check Left
			else if (xPos > -1 && matrix[xPos - 1][yPos] == NULL && checkLeft != pos0 && checkLeft != pos1 && checkLeft != pos2 && checkLeft != pos3)
			{
				xOffset--;
				i = 0;
			}
			// Check Right
			else if (xPos < 10 && matrix[xPos + 1][yPos] == NULL && checkRight != pos0 && checkRight != pos1 && checkRight != pos2 && checkRight != pos3)
			{
				xOffset++;
				i = 0;
			}
			else
			{
				if (currentPosition == position::UP)
				{
					currentPosition = position::RIGHT;
					cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
				}
				else
				{
					currentPosition = currentPosition - 1;
					cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
				}
				break;
			}

		}
	}


	// Draw the Tetromino
	for (SDL_Point& position : cellPositions)
	{

		xPos = position.x + xOffset;
		yPos = position.y + yOffset;
		
		// Update the matricies to represent the change
		matrix[xPos][yPos] = 1 - matrix[xPos][yPos];
		colors[xPos][yPos] = tetrominoColor;
		canRotate = true;
	}



}

void Tetromino::rotateRight(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor)
{
	if (!canRotate)
		return;

	int xPos, yPos;

	// Delete Tetromino from grid
	for (SDL_Point& position : cellPositions)
	{
		// Old Position
		xPos = position.x + xOffset;
		yPos = position.y + yOffset;

		// Remove Color from cell at the Old Position
		matrix[xPos][yPos] = NULL;
		colors[xPos][yPos] = backgroundColor;


	}

	// Apply rotation
	if (currentPosition == position::UP)
	{
		currentPosition = position::RIGHT;
		cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
	}
	else
	{
		currentPosition = currentPosition - 1;
		cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
	}

	for (int i = 0; i < cellPositions.size(); i++)
	{
		xPos = cellPositions[i].x + xOffset;
		yPos = cellPositions[i].y + yOffset;


		if (xPos > 9 || xPos < 0)
		{
			if (currentPosition == position::RIGHT)
			{
				currentPosition = position::UP;
				cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
			}
			else
			{
				currentPosition = currentPosition + 1;
				cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
			}
			break;
		}



		if (matrix[xPos][yPos] != NULL)
		{
			SDL_Point pos0;
			pos0.x = cellPositions[0].x + xOffset;
			pos0.y = cellPositions[0].y + yOffset;
			SDL_Point pos1;
			pos1.x = cellPositions[1].x + xOffset;
			pos1.y = cellPositions[1].y + yOffset;
			SDL_Point pos2;
			pos2.x = cellPositions[2].x + xOffset;
			pos2.y = cellPositions[2].y + yOffset;
			SDL_Point pos3;
			pos3.x = cellPositions[3].x + xOffset;
			pos3.y = cellPositions[3].y + yOffset;

			SDL_Point checkLeft = { xPos - 1, yPos };
			SDL_Point checkRight = { xPos + 1, yPos };
			SDL_Point checkUp = { xPos, yPos - 1 };


			// Check Up
			if (yPos > -1 && matrix[xPos][yPos - 1] == NULL && checkUp != pos0 && checkUp != pos1 && checkUp != pos2 && checkUp != pos3)
			{
				yOffset--;
				i = 0;
			}
			// Check Left
			else if (xPos > -1 && matrix[xPos - 1][yPos] == NULL && checkLeft != pos0 && checkLeft != pos1 && checkLeft != pos2 && checkLeft != pos3)
			{
				xOffset--;
				i = 0;
			}
			// Check Right
			else if (xPos < 10 && matrix[xPos + 1][yPos] == NULL && checkRight != pos0 && checkRight != pos1 && checkRight != pos2 && checkRight != pos3)
			{
				xOffset++;
				i = 0;
			}
			else
			{
				if (currentPosition == position::RIGHT)
				{
					currentPosition = position::UP;
					cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
				}
				else
				{
					currentPosition = currentPosition + 1;
					cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);
				}
				break;
			}

		}
	}


	// Draw the Tetromino
	for (SDL_Point& position : cellPositions)
	{
		// Old Position
		xPos = position.x + xOffset;
		yPos = position.y + yOffset;

		// Update the matricies to represent the change
		matrix[xPos][yPos] = 1 - matrix[xPos][yPos];
		colors[xPos][yPos] = tetrominoColor;

	}
}

void Tetromino::removeTetrominoFromGrid(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor)
{
	int xPos, yPos;


	for (const SDL_Point& position : cellPositions)
	{
		// Positions
		xPos = position.x + xOffset;
		yPos = position.y + yOffset;

		// Remove Color from cell at the Old Position
		matrix[xPos][yPos] = NULL;
		colors[xPos][yPos] = backgroundColor;
	}

	currentPosition = position::UP;
	cellPositions = shapeConfigurations.at(currentTetromino).at(currentPosition);

	xOffset = 0;
	yOffset = 0;
}

void Tetromino::fastDrop(std::vector<std::vector<unsigned char>>& matrix, std::vector<std::vector<SDL_Color>>& colors, const SDL_Color& backgroundColor)
{
	while (!hasLanded)
	{
		moveDown(matrix, colors, backgroundColor);
	}
}


