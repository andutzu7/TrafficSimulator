#include "ObstacleCar.h"

void ObstacleCar::SetSpriteMap()
{
	olc::Sprite* car;

	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\Road\\Aro.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Aro", car));

	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Road\\RomanDiesel.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("RomanDiesel", car));

	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Road\\Taxi.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Taxi", car));
	
	car = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Road\\Lexus.png");
	carState.insert(std::pair<const char*, olc::Sprite*>("Lexus", car));
}

ObstacleCar::ObstacleCar(const Vec2 & startPosition,const int& carNumber)
{
	this->SetPosition(startPosition);
	SetSpriteMap();
	switch (carNumber)
	{
	case 0:
		whichCar = carState["Aro"];
		break;

	case 1:
		whichCar = carState["RomanDiesel"];
			break;
	case 2:
		whichCar = carState["Taxi"];
			break;
	case 3:
		whichCar = carState["Lexus"];
			break;
	default:
		break;
	}
}

 olc::Sprite * ObstacleCar::GetSprite() const
{
	return whichCar;
}
