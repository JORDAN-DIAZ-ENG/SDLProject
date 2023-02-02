#include "Tetromino.h"
#include "Global.h"

#include <SDL.h>

#include <iostream>
#include <vector>
#include <queue>

bool running;

SDL_Renderer* renderer;
SDL_Window* window;

SDL_Color backgroundColor = { 255 / 4, 255 / 4, 255 / 4 };

// Representation of the entire grid
std::vector<std::vector<unsigned char>> matrix(COLUMNS, std::vector<unsigned char>(ROWS));
std::vector<std::vector<SDL_Color>> colors(COLUMNS, std::vector<SDL_Color>(ROWS, backgroundColor));

int counter = 0;
std::vector<int> clearedRows;

std::queue<Tetromino> tetrominoQueue;
std::queue<Tetromino> holdQueue;

bool canHold = true;

Tetromino currentTetromino;

void drawBlockOutsideGrid(int x, int y, int block);


float currentTime = SDL_GetPerformanceCounter();
float lastTime = 0;
float deltaTime;

int gameSpeed = 500;

// Game Loop Functions
void update() 
{
	lastTime = currentTime;
	currentTime = SDL_GetPerformanceCounter();

	deltaTime = (double)((currentTime - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency());


	if (counter * deltaTime > gameSpeed * deltaTime)
	{
		currentTetromino.moveDown(matrix, colors, backgroundColor);
		counter = 0;
		
		if (currentTetromino.isLanded())
		{
			currentTetromino = tetrominoQueue.front();
			tetrominoQueue.pop();

			Tetromino nextInLine;
			tetrominoQueue.push(nextInLine);

			int count = 0;

			for (int r = 0; r < ROWS; r++)
			{

				for (int c = 0; c < COLUMNS; c++)
				{
					if (matrix[c][r] != NULL)
					{
						//std::cout << c << "\t" << r << std::endl;
						count++;
					}

					if (count == COLUMNS)
					{
						for (int i = 0; i < COLUMNS; i++)
						{
							matrix[i][r] = NULL;
							colors[i][r] = backgroundColor;

							for (int row = r; row > 0; row--)
							{
								std::swap(matrix[i][row], matrix[i][row - 1]);
								std::swap(colors[i][row], colors[i][row - 1]);
							}
						}
						clearedRows.push_back(r);

						//std::cout << "\n";
						//std::cout << "LINE CLEARED\n";
					}
				}
				count = 0;

			}
			// Now we need to swap the rows that are cleared with all the ones above it
			//std::cout << "CLEARED ROWS\n";
			//for (int cleared : clearedRows)
			//{
			//
			//	std::cout << cleared << "\n";
			//}
			//std::cout << "\n";

			canHold = true;

		}
	}

}
void input() 
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		// Exit Button
		if (event.type == SDL_QUIT)
			running = false;


		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym) 
			{
			case SDLK_z:
				currentTetromino.rotateLeft(matrix, colors, backgroundColor);
				break;
			case SDLK_x:
				currentTetromino.rotateRight(matrix, colors, backgroundColor);
				break;
			}
		}
		// Keyboard Inputs
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				currentTetromino.moveLeft(matrix, colors, backgroundColor);
				break;
			case SDLK_RIGHT:
				currentTetromino.moveRight(matrix, colors, backgroundColor);
				break;
			case SDLK_DOWN:
				currentTetromino.moveDown(matrix, colors, backgroundColor);
				break;
			case SDLK_c:

				if (!canHold)
					break;

				canHold = false;

				if (holdQueue.empty())
				{
					currentTetromino.removeTetrominoFromGrid(matrix, colors, backgroundColor);
					holdQueue.push(currentTetromino);

					currentTetromino = tetrominoQueue.front();
					tetrominoQueue.pop();
				}
				else
				{
					currentTetromino.removeTetrominoFromGrid(matrix, colors, backgroundColor);
					holdQueue.push(currentTetromino);

					currentTetromino = holdQueue.front();
					holdQueue.pop();
				}
				break;
			case SDLK_SPACE:
				currentTetromino.fastDrop(matrix, colors, backgroundColor);
				break;
			default:
				break;
			}
			
		}

		// Mouse Input
		//if (event.type == SDL_MOUSEBUTTONDOWN)
		//{
		//	int mouseX = event.motion.x;
		//	int mouseY = event.motion.y;

		//	unsigned char cellX = mouseX / CELL_SIZE / RESIZE;
		//	unsigned char cellY = mouseY / CELL_SIZE / RESIZE;

		//	std::cout << "X: " << mouseX / CELL_SIZE / RESIZE << " Y: " << mouseY / CELL_SIZE / RESIZE << std::endl;

		//	if (cellX < 10 && cellY < 20)
		//	{
		//		matrix[cellX][cellY] = 1 - matrix[cellX][cellY]; // 1 - matrix[cellX][cellY] is 0
		//		colors[cellX][cellY] = { 240, 0, 0 };
		//		std::cout << cellX << "\t" << cellY << std::endl;

		//	}
		//}



	}
}
void draw() 
{
	SDL_Rect previewBox;

	previewBox.w = 40;
	previewBox.h = 40;
	previewBox.x = 150;
	previewBox.y = 15;

	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderDrawRect(renderer, &previewBox);

	SDL_Rect boxInsidePreviewBox;

	boxInsidePreviewBox.w = previewBox.w - 2;
	boxInsidePreviewBox.h = previewBox.h - 2;
	boxInsidePreviewBox.x = previewBox.x + 1;
	boxInsidePreviewBox.y = previewBox.y + 1;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, backgroundColor.a);
	SDL_RenderFillRect(renderer, &boxInsidePreviewBox);

	SDL_Rect holdArea;

	holdArea.w = 40;
	holdArea.h = 40;
	holdArea.x = 10;
	holdArea.y = 15;

	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderDrawRect(renderer, &holdArea);

	boxInsidePreviewBox.w = holdArea.w - 2;
	boxInsidePreviewBox.h = holdArea.h - 2;
	boxInsidePreviewBox.x = holdArea.x + 1;
	boxInsidePreviewBox.y = holdArea.y + 1;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, backgroundColor.a);
	SDL_RenderFillRect(renderer, &boxInsidePreviewBox);

	drawBlockOutsideGrid(154, 32, tetrominoQueue.front().getBlockType());

	if (!holdQueue.empty())
		drawBlockOutsideGrid(15, 32, holdQueue.front().getBlockType());


	SDL_Rect cell;
	// Subtracting 1 to height and width for padding
	cell.w = CELL_SIZE - 1;
	cell.h = CELL_SIZE - 1;

	// Draw each cell to the screen
	for (unsigned char i = 0; i < COLUMNS; i++)
	{
		for (unsigned char j = 0; j < ROWS; j++)
		{
			cell.x = CELL_SIZE * i + 60;
			cell.y = CELL_SIZE * j;

			SDL_Color cellColor = colors[i][j];

			SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
			SDL_RenderFillRect(renderer, &cell);
		}
	}

	counter += 1;

	SDL_RenderPresent(renderer); // Needed to draw what was given to the renderer
}




int main(int argc, char* args[])
{
	std::cout << "Arrow Keys: Left and Right\nZ: Rotate Left\nX: Rotate Right\nC: Hold/Replace\nSpace: Fast Drop";

	running = true;

	static int lastTime = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "SDL_Init() failed\n";

	if (SDL_CreateWindowAndRenderer(2.5 * CELL_SIZE * COLUMNS * RESIZE, CELL_SIZE * ROWS * RESIZE, 0, &window, &renderer) < 0)
		std::cout << "SDL_CreateWindowAndRenderer() failed\n";

	SDL_SetWindowTitle(window, "Jetris");
	SDL_ShowCursor(1);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
	SDL_RenderSetScale(renderer, RESIZE, RESIZE);


	Tetromino next1, next2;
	tetrominoQueue.push(next1);
	tetrominoQueue.push(next2);

	//currentTetromino.spawn(matrix);

	// Game Loop
	while (running)
	{


		update();
		input();
		draw();
	}

	//SDL_DestroyTexture(Message);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}



void drawBlockOutsideGrid(int x, int y, int block)
{
	SDL_Rect cell0;
	cell0.h = cell0.w = CELL_SIZE - 1;
	SDL_Rect cell1;
	cell1.h = cell1.w = CELL_SIZE - 1;
	SDL_Rect cell2;
	cell2.h = cell2.w = CELL_SIZE - 1;
	SDL_Rect cell3;
	cell3.h = cell3.w = CELL_SIZE - 1;

	switch (block)
	{

	case 0://I-Block
		cell0.x = x;
		cell0.y = y;
		SDL_SetRenderDrawColor(renderer, 0, 240, 240, 255);
		SDL_RenderFillRect(renderer, &cell0);

		cell1.x = cell0.x + cell1.w + 1;
		cell1.y = y;
		SDL_SetRenderDrawColor(renderer, 0, 240, 240, 255);
		SDL_RenderFillRect(renderer, &cell1);

		cell2.x = cell1.x + cell2.w + 1;
		cell2.y = y;
		SDL_SetRenderDrawColor(renderer, 0, 240, 240, 255);
		SDL_RenderFillRect(renderer, &cell2);

		cell3.x = cell2.x + cell3.w + 1;
		cell3.y = y;
		SDL_SetRenderDrawColor(renderer, 0, 240, 240, 255);
		SDL_RenderFillRect(renderer, &cell3);

		break;
	case 1: //JBLOCK
		cell0.x = x + cell0.w - 2;
		cell0.y = y - cell0.h;
		SDL_SetRenderDrawColor(renderer, 0, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell0);

		cell1.x = cell0.x;
		cell1.y = cell0.y + cell1.h + 1;
		SDL_SetRenderDrawColor(renderer, 0, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell1);

		cell2.x = cell1.x + cell2.w + 1;
		cell2.y = cell1.y;
		SDL_SetRenderDrawColor(renderer, 0, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell2);

		cell3.x = cell2.x + cell3.w + 1;
		cell3.y = cell2.y;
		SDL_SetRenderDrawColor(renderer, 0, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell3);
		break;
	case 2: //LBLOCK
		cell0.x = x + 2;
		cell0.y = y;
		SDL_SetRenderDrawColor(renderer, 240, 160, 0, 255);
		SDL_RenderFillRect(renderer, &cell0);

		cell1.x = cell0.x + cell1.w + 1;
		cell1.y = y;
		SDL_SetRenderDrawColor(renderer, 240, 160, 0, 255);
		SDL_RenderFillRect(renderer, &cell1);

		cell2.x = cell1.x + cell2.w + 1;
		cell2.y = y;
		SDL_SetRenderDrawColor(renderer, 240, 160, 0, 255);
		SDL_RenderFillRect(renderer, &cell2);

		cell3.x = cell2.x;
		cell3.y = y - cell2.h - 1;
		SDL_SetRenderDrawColor(renderer, 240, 160, 0, 255);
		SDL_RenderFillRect(renderer, &cell3);
		break;
	case 3: //OBLOCK
		cell0.x = x + 8;
		cell0.y = y - 6;
		SDL_SetRenderDrawColor(renderer, 240, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell0);

		cell1.x = cell0.x;
		cell1.y = cell0.y + cell1.h + 1;
		SDL_SetRenderDrawColor(renderer, 240, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell1);

		cell2.x = cell1.x + cell2.w + 1;
		cell2.y = cell0.y + cell1.h + 1;
		SDL_SetRenderDrawColor(renderer, 240, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell2);

		cell3.x = cell2.x;
		cell3.y = cell2.y - cell3.h - 1;
		SDL_SetRenderDrawColor(renderer, 240, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell3);
		break;
	case 4://SBLOCK
		cell0.x = x + 5;
		cell0.y = y + 2;
		SDL_SetRenderDrawColor(renderer, 0, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell0);

		cell1.x = cell0.x + cell1.w + 1;
		cell1.y = cell0.y;
		SDL_SetRenderDrawColor(renderer, 0, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell1);

		cell2.x = cell1.x;
		cell2.y = cell1.y - cell2.h - 1;
		SDL_SetRenderDrawColor(renderer, 0, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell2);

		cell3.x = cell2.x + cell3.w + 1;
		cell3.y = cell2.y;
		SDL_SetRenderDrawColor(renderer, 0, 240, 0, 255);
		SDL_RenderFillRect(renderer, &cell3);

		break;
	case 5: //TBLOCK
		cell0.x = x + 4;
		cell0.y = y + 2;
		SDL_SetRenderDrawColor(renderer, 160, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell0);

		cell1.x = cell0.x + cell1.w + 1;
		cell1.y = cell0.y;
		SDL_SetRenderDrawColor(renderer, 160, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell1);

		cell2.x = cell1.x;
		cell2.y = cell1.y - cell2.h - 1;
		SDL_SetRenderDrawColor(renderer, 160, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell2);

		cell3.x = cell2.x + cell3.w + 1;
		cell3.y = cell1.y;
		SDL_SetRenderDrawColor(renderer, 160, 0, 240, 255);
		SDL_RenderFillRect(renderer, &cell3);
		break;
	case 6: //ZBLOCK
		cell0.x = x + 4;
		cell0.y = y - 5;
		SDL_SetRenderDrawColor(renderer, 240, 0, 0, 255);
		SDL_RenderFillRect(renderer, &cell0);

		cell1.x = cell0.x + cell1.w + 1;
		cell1.y = cell0.y;
		SDL_SetRenderDrawColor(renderer, 240, 0, 0, 255);
		SDL_RenderFillRect(renderer, &cell1);

		cell2.x = cell1.x;
		cell2.y = cell1.y + cell2.h + 1;
		SDL_SetRenderDrawColor(renderer, 240, 0, 0, 255);
		SDL_RenderFillRect(renderer, &cell2);

		cell3.x = cell2.x + cell3.w + 1;
		cell3.y = cell2.y;
		SDL_SetRenderDrawColor(renderer, 240, 0, 0, 255);
		SDL_RenderFillRect(renderer, &cell3);
		break;
	default:
		break;
	}

}