#pragma once
#include "Vec2.h"
#include "olcPixelGameEngine.h"
class Tile
{
private:
	
	Vec2 position;
	olc::Pixel color;
public:
	static constexpr size_t width = 100;
	static constexpr size_t length = 50;
	bool draw = true;

	const Vec2 GetPos() const;
	const olc::Pixel GetColor() const;
	void SetPos(Vec2& newPos);
	void SetColor(olc::Pixel color = olc::WHITE);
	
};

