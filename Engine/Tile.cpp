#include "Tile.h"

Tile::Tile(Vei2 position, bool hasBomb)
	:position(position), hasMine(hasBomb)
{

}

void Tile::Draw(Graphics& gfx)
{
	Vei2 centeredPos = { position.x - int(pixelWidth * 0.5f) ,  position.y - int(pixelHeight * 0.5f) };

	if (!isGameOver) {
		switch (state) {
		case State::HIDDEN:
			SpriteCodex::DrawTileButton(centeredPos, gfx);
			break;
		case State::FLAG:
			SpriteCodex::DrawTileButton(centeredPos, gfx);
			SpriteCodex::DrawTileFlag(centeredPos, gfx);
			break;
		case State::REVEALED:
			if (hasMine)
				SpriteCodex::DrawTileBomb(centeredPos, gfx);
			else
				DrawByBombsAround(centeredPos, gfx);
			break;
		}
	}
	else {
		switch (state) {
		case State::HIDDEN:
			if(hasMine)
				SpriteCodex::DrawTileBomb(centeredPos, gfx);
			else
				SpriteCodex::DrawTile0(centeredPos, gfx);
			break;
		case State::FLAG:
			if (hasMine) {
				SpriteCodex::DrawTileBomb(centeredPos, gfx);
				SpriteCodex::DrawTileFlag(centeredPos, gfx);
			}
			else {
				SpriteCodex::DrawTile0(centeredPos, gfx);
				SpriteCodex::DrawTileFlag(centeredPos, gfx);
				SpriteCodex::DrawTileCross(centeredPos, gfx);
			}	
			break;
		case State::REVEALED:
			if(hasMine)
				SpriteCodex::DrawTileBomb(centeredPos, gfx);
			break;
		}
	}
	

}

void Tile::DrawByBombsAround(Vei2& centeredPos, Graphics& gfx)
{
	switch (bombsAroundQty) {
		case 0:
			SpriteCodex::DrawTile0(centeredPos, gfx);
			break;
		case 1:
			SpriteCodex::DrawTile1(centeredPos, gfx);
			break;
		case 2:
			SpriteCodex::DrawTile2(centeredPos, gfx);
			break;
		case 3:
			SpriteCodex::DrawTile3(centeredPos, gfx);
			break;
		case 4:
			SpriteCodex::DrawTile4(centeredPos, gfx);
			break;
		case 5:
			SpriteCodex::DrawTile5(centeredPos, gfx);
			break;
		case 6:
			SpriteCodex::DrawTile6(centeredPos, gfx);
			break;
		case 7:
			SpriteCodex::DrawTile7(centeredPos, gfx);
			break;
		case 8:
			SpriteCodex::DrawTile8(centeredPos, gfx);
			break;
	}
			
}

const Vei2& Tile::GetSize() const
{
	return Vei2(pixelWidth, pixelHeight);
}

bool Tile::HasMine() const
{
	return hasMine;
}

void Tile::AddMine()
{
	hasMine = true;
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

bool Tile::IsFlagged()
{
	return isFlagged;
}

void Tile::RevealTile()
{
	state = State::REVEALED;
}

void Tile::FlagTile()
{
	isFlagged = !isFlagged;

	if (isFlagged)
		state = State::FLAG;
	else
		state = State::HIDDEN;
	
}

void Tile::SetBombsAroundQuantity(int qty)
{
	bombsAroundQty = qty;
}

const Vei2& Tile::GetPosition() const
{
	return position;
}

void Tile::SetGameOver()
{
	isGameOver = true;
}


