#include "Minefield.h"

Minefield::Minefield(int numberOfMines)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, gridWidth - 1);
	std::uniform_int_distribution<int> yDist(0, gridHeight - 1);

	/*for (int i = 0; i < numberOfMines; i++) {

	}*/

	const Vei2 firstTilePosCenter = { gridWorldPosition.x - gridLocalCenterX, gridWorldPosition.y - gridLocalCenterY };

	int index{ 0 };
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++) {

			float posX = firstTilePosCenter.x + (i * Tile::GetPixelWidth());
			float posY = firstTilePosCenter.y + (j * Tile::GetPixelHeight());

			fieldTiles[index++] = Tile(Vei2(posX, posY), false);
			
		}
	}
}

void Minefield::Draw(Graphics& gfx)
{
	gfx.DrawRect(gridWorldPosition, gridPixelWidth, gridPixelHeight, SpriteCodex::baseColor);

	for (Tile& tile : fieldTiles) {
		tile.Draw(gfx);
	}

	//center
	gfx.PutPixel(gridWorldPosition.x, gridWorldPosition.y, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x+1, gridWorldPosition.y, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x-1, gridWorldPosition.y, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x, gridWorldPosition.y+1, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x, gridWorldPosition.y-1, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x + 2, gridWorldPosition.y, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x - 2, gridWorldPosition.y, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x, gridWorldPosition.y + 2, Colors::Green);
	gfx.PutPixel(gridWorldPosition.x, gridWorldPosition.y - 2, Colors::Green);
}

void Minefield::OnBoardClick(Vei2& clickPoint)
{
	for (Tile& tile : fieldTiles) {

		if (tile.IsInsideClickedPoint(clickPoint)) {
			if (!tile.IsRevealed()) {
				tile.RevealTile();
			}
			break;
		}

	}
}


