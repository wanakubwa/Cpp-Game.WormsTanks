#include "Tank.h"

Tank::Tank(const Texture &t, bool canMove, float hp): myTexture(t), canMove(canMove), health(hp)
{
	//inicjacja predkosci oraz parametrow startowych
	size = 40.f;
	speed = 1.f;
	wasStartedVector = false;
	frameCounter = 0;
	frameLimit = 100;
}

Tank::~Tank()
{
}

void Tank::Initialize(const Vector2f &initVectorCurr, const Vector2f &initVectorNext)
{
	tankShape.setSize(Vector2f(size, size));
	tankShape.setTexture(&myTexture);
	Vector2f positionStart = Vector2f(initVectorCurr.x, 20.f);
	tankShape.setPosition(positionStart);
	tankShape.setOrigin(Vector2f(tankShape.getSize().x / 2, tankShape.getSize().y));

	InitRotationRightSite(initVectorCurr, initVectorNext);
}

void Tank::CheckMove(Vector2f groundPos, Vector2f groundNextPos)
{
		UpdateGravity(groundPos);

		if (canMove && isGrounded)
		{
			if ((int)groundPos.x != (int)groundNextPos.x)
			{
				TankMoveInGround(groundPos, groundNextPos);
				frameCounter++;
			}
		}

		if (frameCounter == frameLimit)
		{
			canMove = false;
			frameCounter++;
		}
}

bool Tank::IsGrounded(Vector2f tankPos, Vector2f groundPos)
{
	if (tankPos.y >= groundPos.y)
	return true;

	return false;
}

void Tank::Draw(RenderWindow & w)
{
	w.draw(tankShape);
}

void Tank::ResetTankMove()
{
	canMove = true;
	frameCounter = 0;
}

void Tank::UpdateGravity(Vector2f groundPos)
{
	if (!IsGrounded(tankShape.getPosition(), groundPos))
	{
		isGrounded = false;
		tankShape.move(0.f, 0.5f);
	}
	else
	{
		isGrounded = true;
	}
}

bool Tank::IsTankContains(Vector2f vertex)
{
	if (tankShape.getGlobalBounds().contains(vertex))
		return true;

	return false;
}

int Tank::GetpositionX() const
{
	return (int)tankShape.getPosition().x;
}

float Tank::GetMySize() const
{
	return size;
}

float Tank::GetMySpeed() const
{
	return speed;
}

float Tank::GetMyroration() const
{
	return tankShape.getRotation();
}

float Tank::GetMyHealth() const
{
	return health;
}

bool Tank::GetIsGrounded() const
{
	return isGrounded;
}

Vector2f Tank::GetMySizeVector() const
{
	return tankShape.getSize();
}

Vector2f Tank::GetMyPositionVector() const
{
	return tankShape.getPosition();
}

void Tank::SetCanMove(bool value)
{
	canMove = value;
}

void Tank::SetFrameCounter(int value)
{
	frameCounter = value;
}

void Tank::SetHealth(float valueDown)
{
	health -= valueDown;
}

float Tank::RadianToDegree(float radians)
{
	float degrees;
	degrees = radians * (180.f / PI);
	return degrees;
}

void Tank::InitRotationRightSite(Vector2f initVectorCurr, Vector2f initVectorNext)
{
	if ((int)initVectorCurr.x < (int)initVectorNext.x)//prawo ogolny 
	{
		if (initVectorCurr.y >= initVectorNext.y) //prawo gora
		{
			tankShape.setRotation(-1.f*RadianToDegree(asin(abs(initVectorCurr.y - initVectorNext.y) / sqrt(pow((initVectorCurr.y - initVectorNext.y), 2.f) + pow((initVectorCurr.x - initVectorNext.x), 2.f)))));
		}
		else if (initVectorCurr.y < initVectorNext.y) //prawo dol
		{
			tankShape.setRotation(1.f*RadianToDegree(asin(abs(initVectorCurr.y - initVectorNext.y) / sqrt(pow((initVectorCurr.y - initVectorNext.y), 2.f) + pow((initVectorCurr.x - initVectorNext.x), 2.f)))));
		}
	} //end prawo oolny
}

void Tank::TankMoveInGround(Vector2f & groundPos, Vector2f & groundNextPos)
{
	if ((int)tankShape.getPosition().x < (int)groundNextPos.x)//prawo ogolny 
	{
		if (tankShape.getPosition().y >= groundNextPos.y) //prawo gora
		{
			tankShape.setRotation(-1.f*RadianToDegree(asin(abs(tankShape.getPosition().y - groundNextPos.y) / sqrt(pow((tankShape.getPosition().y - groundNextPos.y), 2.f) + pow((tankShape.getPosition().x - groundNextPos.x), 2.f)))));
			tankShape.move(cos(PI*tankShape.getRotation() / 180.f)*speed, 1.f*sin(PI*tankShape.getRotation() / 180.f)*speed);
		}
		else if (tankShape.getPosition().y < groundNextPos.y) //prawo dol
		{
			tankShape.setRotation(1.f*RadianToDegree(asin(abs(tankShape.getPosition().y - groundNextPos.y) / sqrt(pow((tankShape.getPosition().y - groundNextPos.y), 2.f) + pow((tankShape.getPosition().x - groundNextPos.x), 2.f)))));
			tankShape.move(cos(PI*tankShape.getRotation() / 180.f)*speed, -1.f*sin(PI*tankShape.getRotation() / 180.f)*speed);
		}
	} //end prawo oolny
	else //lewo ogolny 
	{
		if (tankShape.getPosition().y >= groundNextPos.y) //lewo gora
		{
			tankShape.setRotation(1.f* RadianToDegree(asin(abs(tankShape.getPosition().y - groundNextPos.y) / sqrt(pow((tankShape.getPosition().y - groundNextPos.y), 2.f) + pow((tankShape.getPosition().x - groundNextPos.x), 2.f)))));
			tankShape.move(-1.f*cos(PI*tankShape.getRotation() / 180.f)*speed, -1.f*sin(PI*tankShape.getRotation() / 180.f)*speed);
		}
		else if (tankShape.getPosition().y < groundNextPos.y)//lewo dol
		{
			tankShape.setRotation(-1.f* RadianToDegree(asin(abs(tankShape.getPosition().y - groundNextPos.y) / sqrt(pow((tankShape.getPosition().y - groundNextPos.y), 2.f) + pow((tankShape.getPosition().x - groundNextPos.x), 2.f)))));
			tankShape.move(-1.f*cos(PI*tankShape.getRotation() / 180.f)*speed, 1.f*sin(PI*tankShape.getRotation() / 180.f)*speed);
		}
	}//end lewo ogolny
}
