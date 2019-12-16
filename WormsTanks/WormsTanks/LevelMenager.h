#pragma once
#ifndef LEVEL_MENAGER_H
#define LEVEL_MENAGER_H

#include "Settings.h"
#include "GameObj.h"
#include "Menu.h"
#include "WinMenu.h"

class LevelMenager
{
public:
	LevelMenager();
	~LevelMenager();

	void Initialize();
	void RunGame();

private:
	short int levelType;
	short int levelTypeCounter;
	bool errorCheck;
	int playersNumber;
	int landType;
	int keyCode;
	
	string playerName;
	unique_ptr<RenderWindow> window;
	unique_ptr<GameObj> gameObj;
	unique_ptr<Menu> menuObj;
	unique_ptr<WinMenu> winMenuObj;

	void Update();
	void Draw();
	void MakeMainGame();
	void MakeMenu();
	void MakeWinMenu();
	void CheckNextScene();
	void CheckKeyCode(Event &ev);
	void DestroyObjects();
};
#endif