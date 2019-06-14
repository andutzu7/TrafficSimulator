#pragma once
#include "Vec2.h"
#include "olcPixelGameEngine.h"
class Tile //de facut tile clasa abstracta ca sa evit sa incarc in fiecar tile cele 2 tipuri de spriteuri
{
private:
	
	Vec2 position;
	void SetSpriteMap();
public:
	Tile() = default;
	Tile(const Vec2& otherPosition);
	~Tile();
	static constexpr size_t width = 100;
	static constexpr size_t length = 50;
	const Vec2 GetPos() const;
	void SetPos(const Vec2& newPos);
	std::map < const char*, olc::Sprite*> roadTile; //keeping track of the sprite positions by straight up name instead of a big ol switch
	
};

