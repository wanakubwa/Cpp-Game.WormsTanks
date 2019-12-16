#include "Bullet.h"

Bullet::Bullet(float degree, float power, Vector2f motherTankPos)
{
	bulletShape.setSize(Vector2f(10.f, 10.f));
	bulletShape.setFillColor(Color::Red);
	bulletShape.setOrigin(bulletShape.getSize().x / 2.f, bulletShape.getSize().y / 2.f);
	bulletShape.setPosition(motherTankPos);
	startPositionCounter = motherTankPos;
	startedPower = power;
	gravity = 9.7f;
	metersCounter = 0;
	frameCounter = 0;
	speed = 0.2f; //deklaracja predkosci pocisku

	if (degree <= 0) //zamiana na stopnie w ukladzie standardowym
		startDegree = abs(degree);
	else
	{
		startDegree = -1.f*degree + 360.f;
	}
}

Bullet::~Bullet()
{
}

void Bullet::BulletMove()
{
	Time dT;
	dT = deltaClock.getElapsedTime();

		if ((abs(startDegree) >= 0 && abs(startDegree) <= 90) || (abs(startDegree) >= 270 && abs(startDegree) <= 360)) //prawo dowolny zwrot
		{
			if ((int)bulletShape.getPosition().x >= ((int)startPositionCounter.x + metersCounter))
			{
				metersCounter++;
				nextPosVector = Vector2f((int)bulletShape.getPosition().x + 1.f,startPositionCounter.y - (metersCounter*tan((PI / 180.f)*(startDegree)) - (gravity*pow(metersCounter,2)) / (2 * pow(startedPower,2)*pow(cos(PI / 180.f*(startDegree)), 2))));
			}

			if (bulletShape.getPosition().y >= nextPosVector.y) //prawo gora
			{
				bulletShape.setRotation(-1.f*RadianToDegree(asin(abs(bulletShape.getPosition().y - nextPosVector.y) / sqrt(pow((bulletShape.getPosition().y - nextPosVector.y), 2.f) + pow((bulletShape.getPosition().x - nextPosVector.x), 2.f)))));
				bulletShape.move(cos(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds(), 1.f*sin(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds());
			}
			else if (bulletShape.getPosition().y < nextPosVector.y) //prawo dol
			{
				bulletShape.setRotation(1.f*RadianToDegree(asin(abs(bulletShape.getPosition().y - nextPosVector.y) / sqrt(pow((bulletShape.getPosition().y - nextPosVector.y), 2.f) + pow((bulletShape.getPosition().x - nextPosVector.x), 2.f)))));
				bulletShape.move(cos(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds(), 1.f*sin(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds());
			}
		}
		else //lewo dowolny zwrot
		{
			if ((int)bulletShape.getPosition().x <= ((int)startPositionCounter.x - metersCounter))
			{
				metersCounter++;
				nextPosVector = Vector2f((int)bulletShape.getPosition().x - 1.f, startPositionCounter.y + (metersCounter*tan((PI / 180.f)*(startDegree+180.f)) + (gravity*pow(metersCounter, 2)) / (2 * pow(startedPower, 2)*pow(cos(PI / 180.f*(startDegree+180.f)), 2))));
			}
			if (bulletShape.getPosition().y >= nextPosVector.y) //lewo gora
			{
				bulletShape.setRotation(1.f*RadianToDegree(asin(abs(bulletShape.getPosition().y - nextPosVector.y) / sqrt(pow((bulletShape.getPosition().y - nextPosVector.y), 2.f) + pow((bulletShape.getPosition().x - nextPosVector.x), 2.f)))));
				bulletShape.move(-1.f*cos(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds(), -1.f*sin(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds());
			}
			else if (bulletShape.getPosition().y < nextPosVector.y) //lewo dol
			{
				bulletShape.setRotation(-1.f*RadianToDegree(asin(abs(bulletShape.getPosition().y - nextPosVector.y) / sqrt(pow((bulletShape.getPosition().y - nextPosVector.y), 2.f) + pow((bulletShape.getPosition().x - nextPosVector.x), 2.f)))));
				bulletShape.move(-1.f*cos(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds(), -1.f*sin(PI*bulletShape.getRotation() / 180.f)*speed*dT.asMilliseconds());
			}
		}

		deltaClock.restart();
}

void Bullet::Draw(RenderWindow & w)
{
	w.draw(bulletShape);
}

Vector2f Bullet::GetBuletPosVect() const
{
	return bulletShape.getPosition();
}

float Bullet::RadianToDegree(float radians)
{
	float tmp;
	tmp = radians * (180.f / PI);
	return tmp;
}
