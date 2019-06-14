#include "PlayerCar.h"


void PlayerCar::SetSpriteMap()
{
	olc::Sprite* car;

	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\Forward.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Forward", car));
	//aceasta este procedura de adaugat in map. adaugam fiecare sprite cu numele corespunzator
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\leftish.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Leftish", car));
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\LeftMost.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("LeftMost", car));
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\right.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Right", car));
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\rightish.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Rightish", car));
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\SlightlyLeft.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("SlightlyLeft", car));
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\SlightlyRight.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("SlightlyRight", car));
	delete car;
}

PlayerCar::PlayerCar(const Vec2 & startPosition, const size_t & statesNumber)
{
	SetPosition(startPosition);
	SetStatesNumber(statesNumber);//HARD CODAT. NR MEU DE SPRITE URI ESTE 7
	SetSpriteMap();
}
