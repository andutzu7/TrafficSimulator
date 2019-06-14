#include "Tile.h"

const Vec2 Tile::GetPos() const
{
	return position;
}

const olc::Pixel Tile::GetColor() const
{
	return color;
}

void Tile::SetPos( Vec2 & newPos)
{
	position = newPos;
}

void Tile::SetColor(olc::Pixel color)
{
	this->color = color;
}
