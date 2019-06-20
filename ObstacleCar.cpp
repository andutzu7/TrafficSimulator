#include "ObstacleCar.h"

void ObstacleCar::SetSpriteMap()
{
	olc::Sprite* car;

	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\Forward.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Aro", car));

	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\Forward.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("RomanDiesel", car));

	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\Forward.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Taxi", car));
	
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Player\\Forward.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Lexus", car));
}

ObstacleCar::ObstacleCar(const Vec2 & startPosition, const size_t & statesNumber)
{
}
