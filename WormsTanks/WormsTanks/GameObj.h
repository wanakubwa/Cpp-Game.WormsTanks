#pragma once
#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include"Settings.h"
#include"LandCreator.h"
#include "Tank.h"
#include "Artylery.h"
#include "Bullet.h"
#include "UI.h"
#include <vector>
#include <memory>

class GameObj
{
public:
	GameObj(int num, int landType);
	~GameObj();

	void LoadFromFile();
	void Initialize();
	void RefreshGameObj(int keyCode, RenderWindow & w);
	void RefreshBullet();
	void Draw(RenderWindow & w);
	void UpadteIdlePlayer(int number);
	void CheckTankArrow(const int posiotion);

	//gettersy
	bool IsEndGame() const;
	string GetplayerName() const;

private:
	int numOfPlayers;
	int landType;
	int frameCounter;
	int frameLimit;
	float onePlayerSpawn;
	float xInitPos;
	float powerOfBullet;
	bool isEndGame;
	bool wasNextPlayer;
	bool wasArrowSet;

	vector<shared_ptr<Tank>> vectorOfTanks; //inteligentne wskazniki, wektor z obiektami typu tank
	vector<shared_ptr<Artylery>> vectorOfArtylery;
	vector<bool> vectorOfTours;
	shared_ptr<Bullet> bullet;
	unique_ptr<LandCreator> land;
	unique_ptr<UI> uiInterface;

	Texture tankTexture;
	Texture backgroundTexture;
	Sprite backgroundSprite;

	void PowerOfBulletLoad();
	void RestartBulletLoad();
	void KeyCodeDecision(int keyCode, int number);
	void NextPlayer();
	void CheckTankBulletCollision();
	void CheckTanksAlive();
	void LoadTextures();
	void MakeBackground();
	void DestroyBullet();
	bool IsTanksContainsBullet();
};
#endif