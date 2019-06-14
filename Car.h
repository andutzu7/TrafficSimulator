#pragma once
#include "olcPixelGameEngine.h"
#include "Vec2.h"
#include <vector>
#include <map>
class Car
{
private:
	Vec2 position;// to make it const 
	//only for the other cars Vec2 velocity;//movement over time
    size_t statesNumber; //nr of sprites for a single object
protected:

	void  SetStatesNumber(const size_t& s_nr)
	{
			statesNumber = s_nr;

	}
	void SetPosition(const Vec2& pos)
	{
		position = pos;
	}
public://de adaugat gettere
	std::map < const char*, olc::Sprite*> carState; //keeping track of the sprite positions by straight up name instead of a big ol switch
	virtual void SetSpriteMap() = 0;

};
