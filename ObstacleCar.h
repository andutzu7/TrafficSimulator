#pragma once
#include "Car.h"
class ObstacleCar:public Car
{
private:
	olc::Sprite* whichCar;
	void SetSpriteMap();
public:
	ObstacleCar() = default;
	ObstacleCar(const Vec2& startPosition,const int& carNumber);
	olc::Sprite* GetSprite() const;
};

