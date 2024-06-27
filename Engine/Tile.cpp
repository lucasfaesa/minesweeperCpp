#include "Tile.h"

Tile::Tile(Vei2 position, bool hasBomb)
	:position(position), hasBomb(hasBomb)
{

}

void Tile::Draw(Graphics& gfx) const
{
	switch (state) {
		case State::HIDDEN:
			SpriteCodex::DrawTileButton(position, gfx);
			break;
		case State::FLAG:
			SpriteCodex::DrawTileButton(position, gfx);
			SpriteCodex::DrawTileFlag(position, gfx);
			break;
		case State::REVEALED:
			if(hasBomb)
				SpriteCodex::DrawTileBomb(position, gfx);
			else
				SpriteCodex::DrawTile0(position, gfx);
			break;
	}
}

const Vei2& Tile::GetSize() const
{
	return Vei2(pixelWidth, pixelHeight);
}

bool Tile::HasBomb() const
{
	return hasBomb;
}
