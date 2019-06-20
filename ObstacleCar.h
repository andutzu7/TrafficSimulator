#pragma once
#include "Car.h"
class ObstacleCar:public Car
{
private:
	void SetSpriteMap();
public:
	ObstacleCar(const Vec2& startPosition, const size_t& statesNumber = 7);//initial sunt 7 in proiectul meu
};

