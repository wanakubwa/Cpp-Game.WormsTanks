#pragma once
#ifndef LAND_CREATOR_H
#define LAND_CREATOR_H
#include"Settings.h"
#include <ctime>
#include <cmath>
#include <memory>

class LandCreator
{
public:
	LandCreator();
	~LandCreator();

	void Initialize(int type);
	void Draw(RenderWindow &w);
	void DestroyArena(Vector2f positionVect);

	Vector2f GetvectorAt(int xPos) const;
	bool CheckExistPositionAt(int xCheck) const;

private:
	int radius;
	vector<Vector2f> vertexDwnPos;
	vector<Vector2f> vertexUpPos;

	//VertexArray *wskTriangleStrip;
	unique_ptr<VertexArray> wskTriangleStrip;

	void CreateTriangleStrip();
	void DestroyLeftSite(Vector2f &positionVect);
	void DestroyRightSite(Vector2f &positionVect);
	float CheckHeight(int attitude);
};
#endif