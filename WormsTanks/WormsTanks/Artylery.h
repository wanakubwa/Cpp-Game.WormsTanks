#pragma once
#ifndef ARTYLERY_H
#define ARTYLERY_H

#include "Settings.h"
#include <cmath>
#define PI 3.1415926f

class Artylery
{
public:
	Artylery(Vector2f tankPosVect, Vector2f tankSizeVect);
	~Artylery();

	float GetDegrees() const;
	Vector2f GetPositionVect() const;
	Vector2f GetSpawnPosition();

	void UpdatePosition(Vector2f tankPosVect, float tankRotation);
	void UpdateDegrees(const int key);
	void Draw(RenderWindow &w);

	//settersy
	void SetCanMove(bool value);

private:
	Vector2f velocity;
	RectangleShape artyleryShape;
	float degreesRotation;
	float myRotation;
	float tankSizeY;
	float tankSizeX;
	bool canMove;
};
#endif