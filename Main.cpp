#define OLC_PGE_APPLICATION /// DE FACUT FUNCTIE PT UPDATEUL MISCARII SI REZOLVAT CANCERUL ASTA DE PROBLE,A+ADAUGAT PERSPECTIVA
#include "olcPixelGameEngine.h"
#include "PlayerCar.h"
#include "Vec2.h"
#include <vector>
#include <memory>
#include "Tile.h"
///////////////////////VARIABLES AREA\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Vec2 tilePosition(0, 450);
Vec2 carPos(200, 450);
float whereInY = 0.0f;
PlayerCar c(carPos);
size_t tilesOnScreen = 5;
std::vector<Tile*> tiles;
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		sAppName = "Example";
	}
public:
	void Draw() //in aceasta functie desenez spriteul potrivit miscarii masinii
	{//precum si drumurile pe care ne aflam,etc
		//am folosit if else ca sa nu cumva sa se faca overlapping peste desene.
		//pt ca na, nu arata bine
		SetPixelMode(olc::Pixel::ALPHA);
		//asta e o fct ce tine de engine, care deseneaza pixelii din png in functie de transparenta lor
		for (size_t i = 0; i < tilesOnScreen; i++)
		{
			tiles[i]->SetPos(tilePosition);
		
			DrawSprite(tiles[i]->GetPos().x, tiles[i]->GetPos().y, tiles[i]->roadTile["PlayerRoad"], 1);
		}
		DrawSprite(c.GetPosition().x, c.GetPosition().y, c.carState["Forward"], 2);
		 if (GetKey(olc::Key::RIGHT).bHeld)
			
			DrawSprite(carPos.x, carPos.y, c.carState["Right"], 2);
		else
 
		if (GetKey(olc::Key::LEFT).bHeld)
	
			DrawSprite(carPos.x, carPos.y, c.carState["LeftMost"], 2);
		else
		
			if (GetKey(olc::Key::UP).bHeld)
			{
				DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
				tilePosition.y-=1;
				tilePosition.y -= whereInY;
				whereInY += Tile::length;
			}
		

			else 

				if (GetKey(olc::Key::DOWN).bHeld)
				{
					DrawSprite(carPos.x, carPos.y, c.carState["Forward"], 2);
					tilePosition.y += 20;
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
		for (size_t i = 0; i < tilesOnScreen; i++)///initializam vectorul de tiles
		{
			tilePosition.y -= whereInY;
			Tile* t = new Tile(tilePosition);
			tiles.push_back(t);
			whereInY += t->length;
		}
			return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		ClearScreen();
		Draw();
		
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