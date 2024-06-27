#pragma once
#include "Tile.h"
#include <random>
#include "Graphics.h"
#include "Vei2.h"

class Minefield {

public:
	Minefield() = default;
	Minefield(int numberOfMines);
	void Draw(Graphics& gfx);
	void OnBoardClick(Vei2& clickPoint);
private:
	static constexpr int gridWidth = 9;
	static constexpr int gridHeight = 9;

	static constexpr int gridPixelWidth = gridWidth * Tile::GetPixelWidth();
	static constexpr int gridPixelHeight = gridHeight * Tile::GetPixelHeight();

	static constexpr int gridLocalCenterX = gridPixelWidth * 0.5f - Tile::GetPixelWidth() * 0.5f;
	static constexpr int gridLocalCenterY = gridPixelHeight * 0.5f - Tile::GetPixelHeight() * 0.5f;

	Tile fieldTiles[gridWidth * gridHeight];

	const Vei2 gridWorldPosition{ 400,300 };
};