#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Tile {
public:
	enum class State{HIDDEN, FLAG, REVEALED};

	Tile() = default;
	Tile(Vei2 position, bool hasBomb);

	void Draw(Graphics& gfx);

	const Vei2& GetSize() const;
	bool HasMine() const;
	void AddMine();
	bool IsInsideClickedPoint(Vei2& clickedPoint);

	bool IsRevealed();
	bool IsFlagged();
	void RevealTile();
	void FlagTile();

	static constexpr int GetPixelWidth() { return pixelWidth; }
	static constexpr int GetPixelHeight() { return pixelWidth; }
private:
	State state = State::HIDDEN;
	bool hasMine = false;

	static constexpr int pixelWidth { 16 };
	static constexpr int pixelHeight { 16 };
	Vei2 position{};

	bool isFlagged{ false };
};