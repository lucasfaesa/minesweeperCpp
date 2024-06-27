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
	
	const std::vector<Vei2> directions = {
	Vei2(-Tile::GetPixelWidth(), -Tile::GetPixelHeight()), // up-left
	Vei2(0, -Tile::GetPixelHeight()),                     // up
	Vei2(Tile::GetPixelWidth(), -Tile::GetPixelHeight()), // up-right
	Vei2(-Tile::GetPixelWidth(), 0),                      // left
	Vei2(Tile::GetPixelWidth(), 0),                       // right
	Vei2(-Tile::GetPixelWidth(), Tile::GetPixelHeight()), // down-left
	Vei2(0, Tile::GetPixelHeight()),                      // down
	Vei2(Tile::GetPixelWidth(), Tile::GetPixelHeight())   // down-right
	};

	for (int i = 0; i < gridWidth * gridHeight; i++)
	{
		int qty = 0;
		Vei2 currentPos = fieldTiles[i].GetPosition();

		for (const Vei2& direction : directions)
		{
			Vei2 neighborPos = currentPos + direction;

			for (int j = 0; j < gridWidth * gridHeight; j++)
			{
				if (i == j)
					continue;

				if (fieldTiles[j].IsInsideClickedPoint(neighborPos) && fieldTiles[j].HasMine())
				{
					qty++;
				}
			}
		}

		fieldTiles[i].SetBombsAroundQuantity(qty);
	}

}

void Minefield::Draw(Graphics& gfx)
{
	gfx.DrawRect(gridWorldPosition, gridPixelWidth, gridPixelHeight, SpriteCodex::baseColor);

	for (Tile& tile : fieldTiles) {
		tile.Draw(gfx);
	}
}

void Minefield::OnBoardLeftClick(Vei2& clickPoint)
{
	if (isGameOver) return;

	for (Tile& tile : fieldTiles) {

		if (tile.IsInsideClickedPoint(clickPoint)) {
			if (!tile.IsRevealed() && !tile.IsFlagged()) {
				tile.RevealTile();
			}
			if (tile.HasMine())
				SetGameOver();
			break;
		}

	}
}

void Minefield::OnBoardRightClick(Vei2& clickPoint)
{
	if (isGameOver) return;

	for (Tile& tile : fieldTiles) {

		if (tile.IsInsideClickedPoint(clickPoint)) {
			if (!tile.IsRevealed()) {
				tile.FlagTile();
			}
			break;
		}

	}
}

void Minefield::SetGameOver()
{
	isGameOver = true;
	RevealAllTiles();
}

void Minefield::RevealAllTiles()
{
	for (Tile& tile : fieldTiles) {
		if (!tile.IsRevealed()) {
			tile.SetGameOver();
			//tile.RevealTile();
		}
			
	}
}


