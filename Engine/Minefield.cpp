#include "Minefield.h"

Minefield::Minefield(int numberOfMines)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, gridWidth - 1);
	std::uniform_int_distribution<int> yDist(0, gridHeight - 1);

	/*for (int i = 0; i < numberOfMines; i++) {

	}*/

	const Vei2 firstTilePos = { gridWorldPosition.x - gridLocalCenterX, gridWorldPosition.y - gridLocalCenterY };

	int index{ 0 };
	for (int i = 1; i < gridWidth; i++)
	{
		for (int j = 1; j < gridHeight; j++) {

			int posX = firstTilePos.x + (i * Tile::GetPixelWidth());
			int posY = firstTilePos.y + (j * Tile::GetPixelHeight());

			fieldTiles[index++] = Tile(Vei2(posX, posY), false);
			
		}
	}
}

void Minefield::Draw(Graphics& gfx)
{
	for (Tile& tile : fieldTiles) {
		tile.Draw(gfx);
	}
}


