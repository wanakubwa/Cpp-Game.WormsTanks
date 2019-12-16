#pragma once
#ifndef MENU_H
#define MENU_H

#include "Settings.h"
#include <list>

class Menu
{
public:
	Menu();
	~Menu();

	void LoadFromFile();
	void Initialize();
	void Draw(RenderWindow &w);
	void Update(RenderWindow &w);

	//gettersy
	bool GetIsButtonPressed() const;
	int GetPlayersNumber() const;
	int GetLandType() const;

private:
	enum PlayersNumber
	{
		two = 2,
		three = 3,
		four = 4
	};

	enum LandType
	{
		hilly = 0,
		flat = 1
	};

	bool isButtonPressed;
	PlayersNumber playersEnum;
	LandType landTypeEnum;

	RectangleShape playersShape;
	RectangleShape landTypeShape;
	RectangleShape playButtonShape;
	RectangleShape backgroundSprite;

	list<RectangleShape> listPlayerNum;
	list<RectangleShape> listLandType;

	Texture backgroundTexture;
	Texture playButtonTexture;
	Texture playersNumberTexture;
	Texture landTypeTexture;
	Texture twoPlayersTexture;
	Texture threePlayersTexture;
	Texture fourPlayersTexture;
	Texture hillyTexture;
	Texture flatTexture;

	void ListPlayersNumberInitialize();
	void ListLandTypeInitialize();
	void CheckPlayButtonHover(const RenderWindow &w);
	void CheckLandtypeHover(const RenderWindow &w);
	void CheckPlayersNumberHover(const RenderWindow &w);
};
#endif