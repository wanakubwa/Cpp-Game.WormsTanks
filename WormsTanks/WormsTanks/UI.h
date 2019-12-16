#pragma once
#ifndef UI_H
#define UI_H

#include "Settings.h"
#include <memory>
#include <list>
#include <string>

class UI
{
public:
	UI();
	~UI();

	void LoadFromFile();
	void Initialize(const int numberOfPlayers);
	void UpdateUi(float powerOfShot, int maxPower);
	void UpdateHudPosition(int position, Vector2f newPosition, float rotation, float hp, RenderWindow & w);
	void Draw(RenderWindow &w);
	void DeleteHudAtPosition(int i);
	void PlayArrowAt(const Vector2f &position);

	//gettersy
	string GetPlayerName() const;

	//settersy
	void SetDrawableHud(int number);
	void SetIsArrowDrawable(bool value);

private:
	struct OnePlayerHud
	{
		RectangleShape playerHudHitbox;
		RectangleShape playerHealthBar;
		RectangleShape playerHealthBarHov;
		Text nickName;
		bool isDrawable;
		int frameLimit;
		int frameCounter;

		OnePlayerHud(const string &name, const Font &f);
		void DrawHud(RenderWindow &w);
	};

	unsigned int arrowFrameCounter;
	unsigned int arrowFrameLimit;
	bool isArrowDrawable;

	Texture arrowTexture;
	RectangleShape backgroundShape;
	RectangleShape barOfPower;
	RectangleShape playerArrow;
	Font font;

	unique_ptr<VertexArray> barAnimation;
	vector<OnePlayerHud> playerHudArena;
	
	Vector2f arrowVelocity;

	void BarInitialize();
	bool CheckMouseCollision(const RectangleShape &shape, RenderWindow & w);
};
#endif