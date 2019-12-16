#pragma once
#ifndef WIN_MENU_H
#define WIN_MENU_H

#include "Settings.h"

class WinMenu
{
public:
	WinMenu(const string &name);
	~WinMenu();

	void LoadFromFile();
	void Initialize();
	void Draw(RenderWindow &w);
	void Update(RenderWindow &w);

	//gettersy
	bool GetIsButtonPressed() const;

private:
	bool isButtonPressed;

	RectangleShape menuButtonShape;
	RectangleShape backgroundShape;
	string playerName;
	Text playerNumber;


	Texture backgroundTexture;
	Texture menuButtonTexture;
	Font monsterratFont;

	void CheckMenuButtonHover(const RenderWindow &w);
};
#endif