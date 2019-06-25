#define OLC_PGE_APPLICATION /// DE FACUT FUNCTIE PT UPDATEUL MISCARII SI REZOLVAT CANCERUL ASTA DE PROBLE,A+ADAUGAT PERSPECTIVA
#include "olcPixelGameEngine.h"//////TO ADD COMMENTS\\\\\\
#include "PlayerCar.h"
#include "Vec2.h"
#include <vector>
#include <cmath>
#include <memory>
#include <chrono>
#include "PlayerCar.h"
#include "ObstacleCar.h"
//DE ADAUGAT LOGO SAU CV JOS CA SA NU SE MAI VADA BUGU ALA
///TO ADD MOVEMENT BASED ON TIME(aka real life physics + acceleration+more comments+  TO THE PLAYEER aand also make it use velocity
///////////////////////VARIABLES AREA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const int playerWidth = 40;
const int playerHeight = 40;
const int obstacleWidth = 40;
const int obstacleHeight = 40;
const size_t ScreenWidth = 650;//valori hardcodate,se gasesc in consola,nu mi vine nimic mai elegant in minte
Vec2 carPos(ScreenWidth/ 2 - 40, 450); //40 e 1/2 din playerWidth
PlayerCar c(carPos);
float traveledDistance = 0.0f;
float velocity = 0.0f;
olc::Sprite* sky;
ObstacleCar* o;
bool gameOver = false;
const float acceleration = 9.8f;
bool baccOnTracc;
int timePoint=-1;
int actualTime=0;
float speed;
float incrementValue = 0.5f;// ca sa cresc viteza cat timp apas pe o tasta, sa fie speedin
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "C++ Finale";
	}
public:
	void PrintStatus()
	{
		DrawString(0, ScreenHeight() - 20, "Traveled distance: ", olc::BLACK);//Traveled distance
		DrawString(0, ScreenHeight()-10, std::to_string(traveledDistance), olc::BLACK);
		DrawString(0, ScreenHeight() - 40, "Speed: ", olc::BLACK);//Traveled distance
		DrawString(0, ScreenHeight() - 30, std::to_string(speed), olc::BLACK);

 		
	}
	void SpawnObstacle()
	{
		if (o->GetPosition().y < ScreenHeight() / 1.2f && velocity <= 0.0f) //daca playerul sta pe loc in loc sa zboare masina o fac sa dispara din raza  vizuala
		{

			delete o;
			o = new ObstacleCar();
			baccOnTracc = false;
		}
		//asta e ca sa revina totul la normal
		if (o->GetPosition().y > ScreenHeight() + 10) //daca a iesit din ecran
		{
			delete o;
			int carnumber = 0;//ma confrunt cu un cacat de  bug pe care nu il inteleg...
			while (carnumber == 0)
				carnumber = rand() % 4;
			o = new ObstacleCar(Vec2(rand() % (ScreenHeight() / 2) + ScreenHeight() / 3 - 20, ScreenHeight() / 1.8f), carnumber);

		}
		//asta e in cazul in care eram pe loc si m am repus in miscare
		if (!baccOnTracc) ///cod de smecher ortodox
		{
			if (velocity >= 0.1f)//verificam daca ne am repus in miscare
			{
				baccOnTracc = true;
				int carnumber = 0;//ma confrunt cu un cacat de  bug pe care nu il inteleg...

				while (carnumber == 0)
					carnumber = rand() % 4;

			 	o = new ObstacleCar(Vec2(rand() % (ScreenHeight()) + ScreenHeight() / 3, ScreenHeight() / 1.8f), carnumber);
				//generam un nou obstacol care sa apara la orizont
			}
		}

	}
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
				float roadWidth = 0.3f + perspective * 0.8f;//latimea drumului
				float clipWidth = roadWidth * 0.05f;//latimea marginilor miscatoare
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
				borderS = borderShade > 0.0f ? olc::VERY_DARK_GREY : olc::WHITE;
				
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

		//new obstacle stuff
		Vec2 newObstaclePos = o->GetPosition();
		
		//metinem velocitatea in parametri normali
		if (velocity < 0.0f)
			velocity = 0.0f;
		if (velocity > 1.0f)
			velocity = 1.0f;
		DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
		DrawSprite(o->GetPosition().x, o->GetPosition().y, o->GetSprite(),2);
		if (GetKey(olc::Key::RIGHT).bHeld)
		{
			DrawSprite(carPos.x, carPos.y, c.carState["Right"], 2);
			carPos.x += 3.0f;
			velocity += 2.0f*fElapsedTime;
			traveledDistance += speed;
			if (speed < 25.0f)
			speed += incrementValue;
			if (speed > 0.0f)
				newObstaclePos.y += speed / 4;
			else
				newObstaclePos.y += 5;
			o->SetPosition(newObstaclePos);
		}
		 else
 
			if (GetKey(olc::Key::LEFT).bHeld)
			{
				DrawSprite(carPos.x, carPos.y, c.carState["LeftMost"], 2);
				carPos.x -= 3.0f;
				velocity += 2.0f*fElapsedTime;
				traveledDistance += speed;
				if (speed < 25.0f)
				speed += incrementValue;
				if (speed > 0.0f)
					newObstaclePos.y += speed / 4;
				else
					newObstaclePos.y -= 5;
				o->SetPosition(newObstaclePos);
			}
		else
		
			if (GetKey(olc::Key::UP).bHeld)
			{
				DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
				velocity += acceleration*fElapsedTime;
				traveledDistance += speed;
				velocity += 2.0f*fElapsedTime;
				if (speed < 25.0f)
				speed += incrementValue;
				if (speed > 0.0f)
					newObstaclePos.y += speed / 4;
				else
					newObstaclePos.y -= 5;
				o->SetPosition(newObstaclePos);
			}
		else 
  			if (GetKey(olc::Key::DOWN).bHeld)
				{
					DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
					velocity -= 1.8f*velocity*fElapsedTime;
					traveledDistance += speed;
					if (speed > 0.0f)
					{
						newObstaclePos.y += speed / 4;
						speed -= 2*incrementValue;
					}
					else
					{
						speed = 0;
						newObstaclePos.y -= 5;

					}
					o->SetPosition(newObstaclePos);
			}
				else
				{

					DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
					velocity -= 1.0*fElapsedTime;
					traveledDistance += speed;
					if (speed > 0.0f)
						speed -= incrementValue;
					if (speed > 0.0f)
						newObstaclePos.y += speed / 4;
					else
					{
						speed = 0;
						newObstaclePos.y -= 5;

					}

					o->SetPosition(newObstaclePos);
				}
		SetPixelMode(olc::Pixel::NORMAL);
	}
	void ClearScreen()//the usual cleaning screen function called every frame
	{
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::VERY_DARK_BLUE);//ClEARS THE SCREEN

	}
	bool checkCollision(const PlayerCar& a, const ObstacleCar* b)
	{
		const int playerright = a.GetPosition().x + playerWidth/2;
		const int playerleft = a.GetPosition().x - playerWidth / 2;

		const int playerbottom = a.GetPosition().y - playerHeight/2;
		const int playerupper = a.GetPosition().y + playerHeight / 2;

		const int obsright = b->GetPosition().x + obstacleWidth/2;
		const int obsleft = b->GetPosition().x - obstacleWidth / 2;

		const int obsbottom = b->GetPosition().y - obstacleHeight/2;
		const int obsupper = b->GetPosition().y + obstacleHeight / 2;

		return (playerright > obsleft &&
			playerleft < obsright &&
			playerbottom > obsupper &&
			 playerupper < obsbottom);
		
	}
	bool OnUserCreate() override
	{
		int carnumber = 0;//ma confrunt cu un cacat de  bug pe care nu il inteleg...
		while (carnumber == 0)
			carnumber = rand() % 4;
		o = new ObstacleCar(Vec2(rand()%(ScreenHeight()/2)+ScreenHeight()/3, (ScreenHeight()/1.8f)),2);
		sky = new olc::Sprite("D:\\interesting shit\\Traffic simulator\\Project1\\Project1\\Road\\Sky.png");
		timePoint = rand() % 50;
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		if (!gameOver)
		{
			ClearScreen();
			SetPixelMode(olc::Pixel::ALPHA);
			DrawSprite(-100, -100, sky, 3); //drawing the sky
			actualTime++;
			if (actualTime >= timePoint)
			{
				actualTime = 0;
				timePoint = rand() % 50;
				SpawnObstacle();//
			}
			SetPixelMode(olc::Pixel::NORMAL);
			DrawTrack();
			Dravv(fElapsedTime);
			PrintStatus();
		}
		if (checkCollision(c, o))
			gameOver = true;
	
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