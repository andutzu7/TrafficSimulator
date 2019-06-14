#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Vec2.h"
#include "Tile.h"
#include <vector>
//Variables area
Vec2 carPos(255, 255);
Vec2 playerStartPosition(300, 450);
Vec2 actualMovement(300, 450);//cod de kkt , il modific maine
Vec2 tilePosition(250, 450);
std::vector<Tile*>tiles;
Vec2 left(-1, 0);
Vec2 right(1, 0);
Vec2 up(0, -1);
Vec2 down(0, 1);
int nrTilesOnScreen = 2;
float whereInY = 0.0f;//unde spamez urmatorul tile
class Game : public olc::PixelGameEngine
{
public:
	olc::Sprite* car;
	Game()
	{
		sAppName = "Example";
	}
public:
	bool OnUserCreate() override
	{
		car = new olc::Sprite("NES_Touring_police_Car_Sprite_Sheet.png");
		for (size_t i = 0; i < nrTilesOnScreen; i++)
		{
			Tile* t = new Tile();
			tiles.push_back(t);
		}
		for (size_t i = 0; i < nrTilesOnScreen; i++)
		{
			//std::srand(static_cast<int>(time(nullptr)));//for the sweet random seed
			Vec2 newPos = tilePosition;//facem aici o afacere ca sa spawnam astea
			newPos.y -= whereInY;
			tiles[i]->SetPos(newPos);
			whereInY += tiles[i]->length;
			tiles[i]->SetColor(olc::Pixel(rand() % 256, rand() % 256, rand() % 256));

		}

		return true;
	}
	void DrawTile(Tile*t)
	{
		DrawRect(t->GetPos().x, t->GetPos().y, t->width, t->length, t->GetColor());
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		
		FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);//ClEARS THE SCREEN
		SetPixelMode(olc::Pixel::ALPHA);
		DrawSprite(carPos.x,carPos.y, car,2);
		SetPixelMode(olc::Pixel::NORMAL);
		DrawCircle(playerStartPosition.x, playerStartPosition.y, 9);//player
		for (size_t i = 0; i < tiles.size(); i++) 
		{
			/*if (!	(tiles[i]->hasBeenSetUp)	) //tile intialzation
			{
				tiles[i]->hasBeenSetUp = tr,9ue;
				Vec2 newPos = tilePosition;
				newPos.y -= whereInY;
				tiles[i]->SetPos(newPos);
				whereInY += tiles[i]->length;
			}*/
			DrawTile(tiles[i]);
		}
		    if (actualMovement.y > 100000+whereInY)
			{
				Tile*t =new Tile();
			//	t->hasBeenSetUp = true;
				Vec2 newPos = tilePosition;
				newPos.y -= whereInY;
				t->SetPos(newPos);
				whereInY += t->length;
				t->SetColor(olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
				tiles.push_back(t);
			
			}
		if (GetKey(olc::Key::RIGHT).bHeld)
			carPos += right;
		if (GetKey(olc::Key::LEFT).bHeld)
			carPos += left;
		if (GetKey(olc::Key::UP).bHeld)
			carPos += up;
		if (GetKey(olc::Key::DOWN).bHeld)
			carPos += down;
		for (size_t i = 0; i < tiles.size(); i++)
		{
			Vec2 newPos = actualMovement;//facem aici o afacere ca sa spawnam astea
			//newPos.y -= whereInY;
			tiles[i]->SetPos(newPos);
		}
		return true;
	}
};
int main()
{
	Game demo;
	if (demo.Construct(550, 550, 1, 1))
		demo.Start();
	for (auto i : tiles)
	{
		std::cout << i->GetPos().y << " ";
	}
	return 0;
}