#include "Artylery.h"

Artylery::Artylery(Vector2f tankPosVect, Vector2f tankSizeVect)
{
	artyleryShape.setFillColor(Color::Color(34, 47, 70,255));
	artyleryShape.setSize(Vector2f(tankSizeVect.x, 10.f));
	artyleryShape.setOrigin(Vector2f(0.f, artyleryShape.getSize().y / 2.f));
	artyleryShape.setPosition(Vector2f(tankPosVect.x, tankPosVect.y -tankSizeVect.y/2.f));
	tankSizeY = tankSizeVect.y;
	tankSizeX = tankSizeVect.x;
	canMove = true;
	myRotation = 0;
	degreesRotation = 0;
}

Artylery::~Artylery()
{
}

float Artylery::GetDegrees() const
{
	float tmp = (int)myRotation % 360;
	return tmp;
}

Vector2f Artylery::GetPositionVect() const
{
	return artyleryShape.getPosition();
}

Vector2f Artylery::GetSpawnPosition()
{
	float radianAlpha;
	radianAlpha = PI*artyleryShape.getRotation()/180.f;
	Vector2f tmp = Vector2f(artyleryShape.getPosition().x + artyleryShape.getSize().x*cos(radianAlpha), artyleryShape.getPosition().y + artyleryShape.getSize().x*sin(radianAlpha));
	return tmp;
}

void Artylery::UpdatePosition(Vector2f tankPosVect, float tankRotation)
{
	artyleryShape.setPosition(Vector2f(sin(tankRotation*PI/180.f)*tankSizeX / 2.f + tankPosVect.x, tankPosVect.y - cos(PI*tankRotation/180.f)*tankSizeY / 2.f)); //ustawienie dzialka na srodku czolgu
	myRotation = tankRotation - degreesRotation;
	artyleryShape.setRotation(myRotation);
}

void Artylery::UpdateDegrees(const int key)
{
	if(canMove)
	switch (key)
	{
	case 3:
		degreesRotation+=0.5f;
		artyleryShape.setRotation(myRotation - degreesRotation);
		break;
	case 4:
		degreesRotation -= 0.5f;
		artyleryShape.setRotation(myRotation - degreesRotation);
		break;
	default:
		break;
	}
}

void Artylery::Draw(RenderWindow & w)
{
	w.draw(artyleryShape);
}

void Artylery::SetCanMove(bool value)
{
	canMove = value;
}
