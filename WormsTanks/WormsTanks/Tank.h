#pragma once
#ifndef TANK_H
#define TANK_H

#include "Settings.h"
#define PI 3.1415926f

class Tank
{
public:
	Tank(const Texture &t, bool canMove, float hp);
	~Tank();

	void Initialize(const Vector2f &initVectorCurr, const Vector2f &initVectorNext);
	void CheckMove(Vector2f groundPos, Vector2f groundNextPos);
	void Draw(RenderWindow &w);
	void ResetTankMove();
	void UpdateGravity(Vector2f groundPos);
	bool IsTankContains(Vector2f vertex);

	//gettersy
	int GetpositionX() const;
	float GetMySize() const;
	float GetMySpeed() const;
	float GetMyroration() const;
	float GetMyHealth() const;
	bool GetIsGrounded() const;
	Vector2f GetMySizeVector() const;
	Vector2f GetMyPositionVector() const;	

	//settersy
	void SetCanMove(bool value);
	void SetFrameCounter(int value);
	void SetHealth(float valueDown);

private:
	RectangleShape tankShape;
	Vector2f velocity;
	Texture myTexture;

	float speed;
	float size;
	float health;
	int frameCounter;
	int frameLimit;
	bool wasStartedVector;
	bool canMove;
	bool isGrounded;

	bool IsGrounded(Vector2f tankPos, Vector2f groundPos);
	float RadianToDegree(float radians);
	void InitRotationRightSite(Vector2f initVectorCurr, Vector2f initVectorNext);
	void TankMoveInGround(Vector2f &groundPos, Vector2f &groundNextPos);
};
#endif
