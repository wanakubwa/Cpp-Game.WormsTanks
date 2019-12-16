#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "Settings.h"
#include <cmath>
#define PI 3.1415926f

class Bullet
{
public:
	Bullet(float degree, float power, Vector2f motherTankPos);
	~Bullet();

	void BulletMove();
	void Draw(RenderWindow &w);

	Vector2f GetBuletPosVect() const;

private:
	RectangleShape bulletShape;
	Vector2f nextPosVector;
	Vector2f startPositionCounter;

	Clock deltaClock;
	
	float RadianToDegree(float radians);

	float startDegree;
	float startedPower;
	float gravity;
	float speed;
	int metersCounter;
	int frameCounter;
};
#endif