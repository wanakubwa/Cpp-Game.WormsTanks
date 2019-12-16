#include "LandCreator.h"
#include "SimplexNoise.h"

LandCreator::LandCreator()
{
	radius = RADIUS;
}

LandCreator::~LandCreator()
{
}

void LandCreator::Initialize(int type)
{
	srand(time(NULL));

	//dodac wiecej opcji switchem
	float xoff = rand() % 100;
	float scl = SCRNWIDTH / 3.f;
	float yoff = rand() % 100;
	int octaves;
	int loBounds;
	double persistence;
	double scale;

	switch (type)
	{
	case 0: //hilly
		octaves = 6;
		persistence = 0.1;
		scale = 1;
		loBounds = 150;
		break;
	case 1: //flat
		octaves = 3;
		persistence = 0.5;
		scale = 0.5;
		loBounds = 400;
		break;
	default:
		break;
	}
	
	for (int i = 0; i <= SCRNWIDTH; i ++) {
		vertexDwnPos.push_back(Vector2f(i, SCRNHEIGHT));
		if ((i + 2)>SCRNWIDTH && vertexDwnPos.back()!=Vector2f(SCRNWIDTH,SCRNHEIGHT)) //rozbic na 2 ify w celu optymalizacji
		{
			vertexDwnPos.push_back(Vector2f(SCRNWIDTH, SCRNHEIGHT));
		}
	}

	for (int i = 0; i <= SCRNWIDTH; i ++) {
		vertexUpPos.push_back(Vector2f(i, scaled_octave_noise_2d(octaves, persistence, scale, loBounds, SCRNHEIGHT,(i+xoff)/scl, yoff/scl)));
		if ((i + 2) >SCRNWIDTH && vertexUpPos.back().x != SCRNWIDTH) //rozbic na 2 ify w celu optymalizacji
		{
			vertexUpPos.push_back(Vector2f(SCRNWIDTH, scaled_octave_noise_2d(octaves, persistence, scale, loBounds, SCRNHEIGHT, (i + xoff) / scl, yoff / scl)));
		}
		xoff += 0.001;
	}
	CreateTriangleStrip();
}

void LandCreator::Draw(RenderWindow & w)
{
	w.draw(*(wskTriangleStrip.get()));
}

void LandCreator::DestroyArena(Vector2f positionVect)
{
	DestroyLeftSite(positionVect);
	DestroyRightSite(positionVect);
	CreateTriangleStrip();
}

Vector2f LandCreator::GetvectorAt(int xPos) const
{
	Vector2f vectorAt = vertexUpPos.at(xPos);
	return vectorAt;
}

bool LandCreator::CheckExistPositionAt(int xCheck) const
{
	if (xCheck >= vertexUpPos.size() || xCheck<0)
		return false;
	return true;
}

void LandCreator::CreateTriangleStrip()
{
	int vertexUpCounter = 0;
	int vertexDwnCounter = 0;
	wskTriangleStrip = make_unique<VertexArray>(TrianglesStrip, (vertexDwnPos.size() + vertexUpPos.size()));
	
	for (int i = 0; i < (vertexDwnPos.size() + vertexUpPos.size()); i++) {
		if (i%2==0)
		{
			(*(wskTriangleStrip.get()))[i].position = vertexUpPos.at(vertexUpCounter);
			(*(wskTriangleStrip.get()))[i].color = Color::Color(194, 94, 34,255);
			vertexUpCounter++;
		}
		else
		{
			(*(wskTriangleStrip.get()))[i].position = vertexDwnPos.at(vertexDwnCounter);
			(*(wskTriangleStrip.get()))[i].color = Color::Color(255, 241, 141, 255);;
			vertexDwnCounter++;
		}
	}
}

void LandCreator::DestroyLeftSite(Vector2f & positionVect)
{
	float height = 0.f;
	float tmp = 0.f;

	for (int i = 0; i <= radius; i++) {
		if ((int)positionVect.x - i >= 0) //czy nie przekracza z lewej strony 0 moze byc bo numeracja od 0
		{
			tmp = vertexUpPos.at((int)positionVect.x - i).y;
			if (tmp < positionVect.y) //jest nad srodkiem
			{
				height = CheckHeight(i);
				if (tmp > positionVect.y - height) // jest w kole
				{
					height = positionVect.y - tmp;
					height += CheckHeight(i);
					if (tmp + height > SCRNHEIGHT) //czy nie wypadl na dole
					{
						vertexUpPos.at((int)positionVect.x - i).y = SCRNHEIGHT;
					}
					else
					{
						vertexUpPos.at((int)positionVect.x - i).y += height;
					}
				}
				else //jest nad kolem
				{
					if (tmp + 2 * height > SCRNHEIGHT)
					{
						vertexUpPos.at((int)positionVect.x - i).y = SCRNHEIGHT;
					}
					else
					{
						vertexUpPos.at((int)positionVect.x - i).y += 2 * height;
					}
				}
			}
			else //jest pod srodkiem
			{
				height = CheckHeight(i);
				if (tmp < positionVect.y + height) //jest w kole
				{
					height = height - (tmp - positionVect.y);
					if (tmp + height > SCRNHEIGHT) //przekroczenie wysokosci
					{
						vertexUpPos.at((int)positionVect.x - i).y = SCRNHEIGHT;
					}
					else
					{	
						vertexUpPos.at((int)positionVect.x - i).y += height;
					}
				}
			}
		}
	}
}

void LandCreator::DestroyRightSite(Vector2f & positionVect)
{
	float height = 0.f;
	float tmp = 0.f;

	for (int i = 1; i <= radius; i++) {
		if ((int)positionVect.x + i < SCRNWIDTH) //czy nie przekracza z prawej strony 0 moze byc bo numeracja od 0
		{
			tmp = vertexUpPos.at((int)positionVect.x + i).y;
			if (tmp < positionVect.y) //jest nad srodkiem
			{
				height = CheckHeight(i);
				if (tmp > positionVect.y - height) // jest w kole
				{
					height = positionVect.y - tmp;
					height += CheckHeight(i);
					if (tmp + height > SCRNHEIGHT) //czy nie wypadl na dole
					{
						vertexUpPos.at((int)positionVect.x + i).y = SCRNHEIGHT;
					}
					else
					{
						vertexUpPos.at((int)positionVect.x + i).y += height;
					}
				}
				else //jest nad kolem
				{
					if (tmp + 2 * height > SCRNHEIGHT)
					{
						vertexUpPos.at((int)positionVect.x + i).y = SCRNHEIGHT;
					}
					else
					{
						vertexUpPos.at((int)positionVect.x + i).y += 2 * height;
					}
				}
			}
			else //jest pod srodkiem
			{
				height = CheckHeight(i);
				if (tmp < positionVect.y + height) //jest w kole
				{
					height = height - (tmp - positionVect.y);
					if (tmp + height > SCRNHEIGHT) //przekroczenie wysokosci
					{
						vertexUpPos.at((int)positionVect.x + i).y = SCRNHEIGHT;
					}
					else
					{
						vertexUpPos.at((int)positionVect.x + i).y += height;
					}
				}
			}
		}
	}
}

float LandCreator::CheckHeight(int attitude)
{
	float tmp = sqrt(pow(radius, 2.f) - pow(attitude, 2.f));
	return tmp;
}