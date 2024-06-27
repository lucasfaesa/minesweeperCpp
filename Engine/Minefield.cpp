#include "Minefield.h"

Minefield::Minefield(int numberOfMines)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> dist(0, gridWidth * gridHeight - 1);

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

	int countMines{ 0 };

	do
	{
		if (!fieldTiles[dist(rng)].HasMine()) {
			fieldTiles[dist(rng)].AddMine();
			countMines++;
		}

	} while (countMines != numberOfMines);
	
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

void Minefield::OnBoardLeftClick(Vei2& clickPoint)
{
	for (Tile& tile : fieldTiles) {

		if (tile.IsInsideClickedPoint(clickPoint)) {
			if (!tile.IsRevealed() && !tile.IsFlagged()) {
				tile.RevealTile();
			}
			break;
		}

	}
}

void Minefield::OnBoardRightClick(Vei2& clickPoint)
{
	for (Tile& tile : fieldTiles) {

		if (tile.IsInsideClickedPoint(clickPoint)) {
			if (!tile.IsRevealed()) {
				tile.FlagTile();
			}
			break;
		}

	}
}


