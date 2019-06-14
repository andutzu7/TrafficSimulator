#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "PlayerCar.h"
#include "Vec2.h"
#include <vector>
Vec2 carPos(200, 450);
PlayerCar c(carPos);
class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "Example";
	}
public:
	void DrawCarState() //in aceasta functie desenez spriteul potrivit miscarii masinii
	{
		//am folosit if else ca sa nu cumva sa se faca overlapping peste desene.
		//pt ca na, nu arata bine
		SetPixelMode(olc::Pixel::ALPHA);
		//asta e o fct ce tine de engine, care deseneaza pixelii din png in functie de transparenta lor
		    DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
		
		if (GetKey(olc::Key::RIGHT).bHeld)
			
			DrawSprite(carPos.x, carPos.y, c.carState["Right"], 2);
		else
 
		if (GetKey(olc::Key::LEFT).bHeld)
	
			DrawSprite(carPos.x, carPos.y, c.carState["LeftMost"], 2);
		else
		
		if (GetKey(olc::Key::UP).bHeld)
		
			DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
		else 

		if (GetKey(olc::Key::DOWN).bHeld)
		
			DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
		
		SetPixelMode(olc::Pixel::NORMAL);
		//asta e ca sa revina totul la normal
	}
	void ClearScreen()//the usual cleaning screen function called every frame
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::VERY_DARK_BLUE);//ClEARS THE SCREEN

	}
	bool OnUserCreate() override
	{
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		ClearScreen();
		DrawCarState();
		
		return true;
	}
};
int main()
{
	Game demo;
	if (demo.Construct(550, 550, 1, 1))
		demo.Start();
	std::cin.get();
	return 0;
}