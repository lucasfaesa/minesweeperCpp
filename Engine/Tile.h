#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Tile {
public:
	enum class State{HIDDEN, FLAG, REVEALED};

	Tile() = default;
	Tile(Vei2 position, bool hasBomb);

	void Draw(Graphics& gfx) const;

	const Vei2& GetSize() const;
	bool HasBomb() const;

	static constexpr int GetPixelWidth() { return pixelWidth; }
	static constexpr int GetPixelHeight() { return pixelWidth; }
private:
	State state = State::HIDDEN;
	bool hasBomb = false;

	static constexpr int pixelWidth { 20 };
	static constexpr int pixelHeight { 20 };
	Vei2 position{};
};