#include "Tile.h"

Tile::Tile(Vei2 position, bool hasBomb)
	:position(position), hasBomb(hasBomb)
{

}

void Tile::Draw(Graphics& gfx)
{
	Vei2 centeredPos = { position.x - int(pixelWidth * 0.5f) ,  position.y - int(pixelHeight * 0.5f) };

	switch (state) {
		case State::HIDDEN:
			SpriteCodex::DrawTileButton(centeredPos, gfx);
			break;
		case State::FLAG:
			SpriteCodex::DrawTileButton(centeredPos, gfx);
			SpriteCodex::DrawTileFlag(centeredPos, gfx);
			break;
		case State::REVEALED:
			if(hasBomb)
				SpriteCodex::DrawTileBomb(centeredPos, gfx);
			else
				SpriteCodex::DrawTile0(centeredPos, gfx);
			break;
	}

	//center
	gfx.PutPixel(position.x, position.y, Colors::Red);
}

const Vei2& Tile::GetSize() const
{
	return Vei2(pixelWidth, pixelHeight);
}

bool Tile::HasBomb() const
{
	return hasBomb;
}

bool Tile::IsInsideClickedPoint(Vei2& clickedPoint)
{
	const int xMin = position.x - int(pixelWidth * 0.5f);
	const int xMax = position.x + int(pixelWidth * 0.5f);
	const int yMin = position.y - int(pixelHeight * 0.5f);
	const int yMax = position.y + int(pixelHeight * 0.5f);

	return xMin <= clickedPoint.x &&
			xMax >= clickedPoint.x &&
			yMin <= clickedPoint.y &&
			yMax >= clickedPoint.y;
}

bool Tile::IsRevealed()
{
	return state == State::REVEALED;
}

void Tile::RevealTile()
{
	state = State::REVEALED;
}
