#pragma once
#include "Car.h"

class PlayerCar : public Car
{
private:
	void SetSpriteMap();
public:
	PlayerCar(const Vec2& startPosition, const size_t& statesNumber=7);//initial sunt 7 in proiectul meu

};