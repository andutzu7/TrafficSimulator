#include "Tile.h"

Tile::Tile(const Vec2 & otherPosition)
{
	SetPos(otherPosition);
	SetSpriteMap();
}

Tile::~Tile()
{
	roadTile.clear();
}

const Vec2 Tile::GetPos() const
{
	return position;
}

void Tile::SetPos(const Vec2 & newPos)
{
	position = newPos;
}

void Tile::SetSpriteMap()
{
	olc::Sprite* road;
	road = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Road\\PlayerRoad.png");
	roadTile.insert(std::pair<const char*, olc::Sprite*>("PlayerRoad", road));
	road = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Road\\OtherRoad.png");
	roadTile.insert(std::pair<const char*, olc::Sprite*>("OtherRoad", road));
	delete road;
}

