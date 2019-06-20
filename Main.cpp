#define OLC_PGE_APPLICATION /// DE FACUT FUNCTIE PT UPDATEUL MISCARII SI REZOLVAT CANCERUL ASTA DE PROBLE,A+ADAUGAT PERSPECTIVA
#include "olcPixelGameEngine.h"
#include "PlayerCar.h"
#include "Vec2.h"
#include <vector>
#include <cmath>
#include <memory>
#include "Tile.h"
///TO ADD MOVEMENT BASED ON TIME(aka real life physics + acceleration+more comments+  TO THE PLAYEER aand also make it use velocity
///////////////////////VARIABLES AREA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const size_t ScreenWidth = 650;//valori hardcodate,se gasesc in consola,nu mi vine nimic mai elegant in minte
Vec2 carPos(ScreenWidth/ 2 - 40, 450); //40 e 1/2 din playerWidth
PlayerCar c(carPos);
float traveledDistance = 0.0f;
float velocity = 0.0f;
olc::Sprite* sky;

///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "Crasher";
	}
public:
	
	void DrawTrack()
	{
		for (size_t y = 0; y < ScreenHeight() / 2; y++) //iteram prin tot ecranu ca sav vedem daca e iarba margine sau drum
			for (size_t x = 0; x < ScreenWidth(); x++)
			{
				float perspective = (float)y / (ScreenHeight() / 2.0f);
				/*
				Perspectiva are o formula foarte frumoasa. In functie de pozitia pe y pe care ne aflam
				impartim nr actual astfel incat sa dea iluzia de distanta. Acest lucru este
				cauzat de faptul ca y are valori diferite. Cu cat suntem mai in josul ecranului,
				y are val mai mare iar perspectiva are valoare mai mare. Cand ne indepartam nr reultat este mai
				mic, si totodata ni se pare ca distanta se mareste. Chiar am inteles o si e smechera, o s o mai folosesc
				*/
				float MiddlePoint = 0.5f; //mijlocu ecranului
				float roadWidth = 0.1f + perspective * 0.8f;//latimea drumului
				float clipWidth = roadWidth * 0.15f;//latimea marginilor miscatoare
			///Aici detemrin exact puntele. Avem mijlocul ecranului
				roadWidth *= 0.5f;//injumatatim latimea drumului
				size_t leftGrass = (MiddlePoint - roadWidth - clipWidth)*ScreenWidth();
				size_t leftTrackMargin = (MiddlePoint - roadWidth)*ScreenWidth();
				size_t rightGrass = (MiddlePoint + roadWidth + clipWidth)*ScreenWidth();
				size_t rightTrackMargin = (MiddlePoint + roadWidth)*ScreenWidth();



				float grassShade = std::sin(20.0f* std::pow(1.0f - perspective, 3) + traveledDistance * 0.1f); //aici folosesc lambda ul
				//o functie matematica care imi genereaza valorile de verde din iarba; e luata de pe net, nu are rost sa ma chinui s o inteleg
				float borderShade = std::sin(80.0f* std::pow(1.0f - perspective, 3) + traveledDistance * 0.1f); //aici folosesc lambda ul

				olc::Pixel grassC;
				olc::Pixel borderS;
				if (grassShade > 0.0f)
					grassC = olc::VERY_DARK_GREEN;
				else
					grassC = olc::DARK_GREEN;
				///EXPERIMENTAL ONE LINE IF, DONT WORRY IT S COOL
				borderS = borderShade > 0.0f ? olc::RED : olc::WHITE;
				
				const size_t rowNumber = ScreenWidth() / 2 + y;
			
				olc::Pixel middleLineColor;
				
				float middleLineShade = std::sin(80.0f* std::pow(1.0f - perspective, 3) + traveledDistance * 0.1f); //aici folosesc lambda ul
				
				if (middleLineShade > 0.0f)
					middleLineColor = olc::VERY_DARK_GREY;
				else
					middleLineColor = olc::WHITE;
				
				if (x >= 0 && x < leftGrass)
				{
					Draw(x, rowNumber, grassC);
				}
				if (x >= leftGrass && x < leftTrackMargin)
				{
					Draw(x, rowNumber, borderS);
				}
				if (x >= leftTrackMargin && x <= rightTrackMargin)
				{
					Draw(x, rowNumber, olc::VERY_DARK_GREY);
				}
				if (x >= rightTrackMargin && x < rightGrass)
				{
					Draw(x, rowNumber, borderS);
				}
				if (x >= rightGrass && x < ScreenWidth())
				{
					Draw(x, rowNumber, grassC);
				}
				
				if (x >= MiddlePoint * ScreenWidth() - 1 && x <= MiddlePoint * ScreenWidth() + 1)
				{   //LINIA CENTRALA
				//	if (rowNumber % 10 > 5) // Am incropit o conditie 100% originala si sint mindru
						Draw(x, rowNumber, middleLineColor);
				}

			}
	}
	void Dravv(float fElapsedTime) //in aceasta functie desenez spriteul potrivit miscarii masinii
	{//precum si drumurile pe care ne aflam,etc
		//am folosit if else ca sa nu cumva sa se faca overlapping peste desene.
		//pt ca na, nu arata bine
		SetPixelMode(olc::Pixel::ALPHA);
		//asta e o fct ce tine de engine, care deseneaza pixelii din png in functie de transparenta lor
	
		if (velocity < 0.0f)
			velocity = 0.0f;
		if (velocity > 1.0f)
			velocity = 1.0f;
		DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
		if (GetKey(olc::Key::RIGHT).bHeld)
		{
			carPos.x += 3.0f;
			DrawSprite(carPos.x, carPos.y, c.carState["Right"], 2);
			traveledDistance += 200.0f*velocity*fElapsedTime;
			velocity += 2.0f*fElapsedTime;
		}
		 else
 
			if (GetKey(olc::Key::LEFT).bHeld)
			{
				DrawSprite(carPos.x, carPos.y, c.carState["LeftMost"], 2);
				carPos.x -= 3.0f;
				traveledDistance += 200.0f*velocity*fElapsedTime;
				velocity += 2.0f*fElapsedTime;
			}
		else
		
			if (GetKey(olc::Key::UP).bHeld)
			{
				DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
				traveledDistance += 200.0f*velocity*fElapsedTime;
				velocity += 2.0f*fElapsedTime;
			}
		else 
  			if (GetKey(olc::Key::DOWN).bHeld)
				{
					DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
					traveledDistance += 50.0f * velocity*fElapsedTime;

					velocity -= 1.8f*velocity*fElapsedTime;
				
			}
				else
				{

					DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
					traveledDistance += 200 * velocity*fElapsedTime;
					velocity -= 1.0*fElapsedTime;

				}
		SetPixelMode(olc::Pixel::NORMAL);
		//asta e ca sa revina totul la normal

	}
	void ClearScreen()//the usual cleaning screen function called every frame
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::VERY_DARK_BLUE);//ClEARS THE SCREEN

	}
	bool OnUserCreate() override
	{
		sky = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Road\\Sky.png");
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		//ClearScreen();//draw sky
		SetPixelMode(olc::Pixel::ALPHA);

		DrawSprite(-100, -100, sky,3);
		SetPixelMode(olc::Pixel::NORMAL);
		DrawTrack();
		Dravv(fElapsedTime);
		return true;
	}
};
int main()
{
	Game demo;
	if (demo.Construct(650, 550, 1, 1))
		demo.Start();
	
	return 0;
}