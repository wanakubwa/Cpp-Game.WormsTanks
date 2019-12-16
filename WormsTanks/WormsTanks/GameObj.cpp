#include "GameObj.h"

GameObj::GameObj(int num, int landType) : numOfPlayers(num), landType(landType)
{
	land = make_unique<LandCreator>(); //tworzenie unikalnego i jedynego wskaznika na kreatora
	uiInterface = make_unique<UI>(); //tworzenie unikalnego wskaznika na ui
	onePlayerSpawn = SCRNWIDTH / numOfPlayers;
	frameCounter = 0;
	frameLimit = 100;
	powerOfBullet = 0.f;
	isEndGame = false;
	wasArrowSet = false;
}

GameObj::~GameObj()
{
}

void GameObj::LoadFromFile()
{
	int error = 201;

	try
	{
		uiInterface->LoadFromFile();
		LoadTextures();
	}

	catch (...)
	{
		uiInterface.reset();
		land.reset();
		throw error;
	}
}

void GameObj::Initialize()
{
	MakeBackground();

	land->Initialize(landType);
	uiInterface->Initialize(numOfPlayers);

	for (int i = 0; i < numOfPlayers; i++) {
		xInitPos = onePlayerSpawn / 2 + i*onePlayerSpawn;

		shared_ptr<Tank> _newTank(new Tank(tankTexture, true, 100.f)); //jawne wywolanie wspoldzielonego wskaznika na klase Tank
		_newTank->Initialize(land.get()->GetvectorAt(xInitPos), land.get()->GetvectorAt(xInitPos + 1)); //inicjalizacja obiektu
		vectorOfTanks.push_back(move(_newTank)); //przeniesienie wskaznika do wektora

		if (i == 0)
			vectorOfTours.push_back(true);
		else
			vectorOfTours.push_back(false);

		shared_ptr<Artylery> _newArtylery(new Artylery(vectorOfTanks[i].get()->GetMyPositionVector(), vectorOfTanks[i].get()->GetMySizeVector()));
		vectorOfArtylery.push_back(move(_newArtylery)); //przeniesienie wskaznika
	}
}

void GameObj::RefreshGameObj(int keyCode, RenderWindow & w)
{
	for (int i = 0; i < vectorOfTanks.size(); i++) 
	{
		if (vectorOfTours[i])
		{
			CheckTankArrow(i);
			KeyCodeDecision(keyCode,i);
		}
		else
		{
			UpadteIdlePlayer(i);
		}

		uiInterface->UpdateUi(powerOfBullet, frameLimit);

		if (i < vectorOfTanks.size())
			uiInterface->UpdateHudPosition(i, vectorOfTanks[i]->GetMyPositionVector(), vectorOfTanks[i]->GetMyroration(), vectorOfTanks[i]->GetMyHealth(), w);
	}
}

void GameObj::RefreshBullet()
{
	if (bullet.get()->GetBuletPosVect().x < SCRNWIDTH && bullet.get()->GetBuletPosVect().x >= 0)
	{
		if (IsTanksContainsBullet())
		{
			DestroyBullet();
		}

		else if (land.get()->GetvectorAt((int)bullet.get()->GetBuletPosVect().x).y <= bullet.get()->GetBuletPosVect().y)
		{
			DestroyBullet();
		}
		else
		{
			bullet.get()->BulletMove();
		}
	}
	else
	{
		bullet.reset(); //resetowanie wskaznika na bullet
		NextPlayer();
	}
}

void GameObj::Draw(RenderWindow & w)
{
	w.draw(backgroundSprite);

	if (bullet)
		bullet.get()->Draw(w);
	land.get()->Draw(w); //wyswietlenie gory

	for (auto &it : vectorOfArtylery) //wykorzystanie iteratorow
	{
		it->Draw(w);
	}

	for (auto &it : vectorOfTanks) //wykorzystanie iteratorow 
	{
		it->Draw(w);
	}

	uiInterface.get()->Draw(w);
}

void GameObj::UpadteIdlePlayer(int number)
{
	vectorOfTanks[number].get()->UpdateGravity(land.get()->GetvectorAt(vectorOfTanks[number].get()->GetpositionX()));
	vectorOfArtylery[number].get()->UpdatePosition(vectorOfTanks[number].get()->GetMyPositionVector(), vectorOfTanks[number].get()->GetMyroration());
}

void GameObj::CheckTankArrow(const int posiotion)
{
	if (!wasArrowSet)
	{
		if (vectorOfTanks[posiotion]->GetIsGrounded())
		{
			uiInterface->PlayArrowAt(vectorOfTanks[posiotion]->GetMyPositionVector());
			uiInterface->SetIsArrowDrawable(true);
		}
	}
	else
	{
		uiInterface->SetIsArrowDrawable(false);
	}
		
}

bool GameObj::IsEndGame() const
{
	return isEndGame;
}

string GameObj::GetplayerName() const
{
	return uiInterface->GetPlayerName();
}

void GameObj::PowerOfBulletLoad()
{
	if (frameCounter <= frameLimit)
	{
		powerOfBullet += 1.f;
		frameCounter++;
	}
}

void GameObj::RestartBulletLoad()
{
	frameCounter = 0;
	powerOfBullet = 0.f;
}

void GameObj::KeyCodeDecision(int keyCode, int number)
{	
		switch (keyCode)
		{
		case 1: //prawo
			if (land.get()->CheckExistPositionAt(vectorOfTanks[number].get()->GetpositionX() + vectorOfTanks[number].get()->GetMySize() / 4.f)) //1/4 rozmiaru jako punk odniesienia
			{
				vectorOfTanks[number].get()->CheckMove(land.get()->GetvectorAt(vectorOfTanks[number].get()->GetpositionX()), land.get()->GetvectorAt(vectorOfTanks[number].get()->GetpositionX() + vectorOfTanks[number].get()->GetMySize() / 4.f)); //.get zwraca adres wskaznika, uzycie jak adrsu zwyklego
				wasArrowSet = true;
			}
			break;
		case 2:
			if (land.get()->CheckExistPositionAt(vectorOfTanks[number].get()->GetpositionX() - vectorOfTanks[number].get()->GetMySize() / 4.f))
			{
				vectorOfTanks[number].get()->CheckMove(land.get()->GetvectorAt(vectorOfTanks[number].get()->GetpositionX()), land.get()->GetvectorAt(vectorOfTanks[number].get()->GetpositionX() - vectorOfTanks[number].get()->GetMySize() / 4.f)); //.get zwraca adres wskaznika, uzycie jak adrsu zwyklego
				wasArrowSet = true;
			}
			break;
		default:
			vectorOfTanks[number].get()->CheckMove(land.get()->GetvectorAt(vectorOfTanks[number].get()->GetpositionX()), land.get()->GetvectorAt(vectorOfTanks[number].get()->GetpositionX()));
			if (keyCode == 3 || keyCode == 4) //zmiena nachylenia armatki
			{
				vectorOfTanks[number].get()->SetCanMove(false);
				vectorOfArtylery[number].get()->UpdateDegrees(keyCode);
				wasArrowSet = true;
			}
			if (keyCode == 5) {
				if (!bullet)
				{
					vectorOfArtylery[number].get()->SetCanMove(false);
					PowerOfBulletLoad();
				}
				wasArrowSet = true;
			}
			if (keyCode == 6)
			{
				if (!bullet)
				{
					bullet = make_shared<Bullet>(vectorOfArtylery[number].get()->GetDegrees(), powerOfBullet, vectorOfArtylery[number].get()->GetSpawnPosition());
					RestartBulletLoad();
				}
				wasArrowSet = true;
			}
			break;
		}
		if (bullet) //tylko wlasciciel ma dostep
		{
			RefreshBullet();
		}
	if(number<vectorOfArtylery.size())
		vectorOfArtylery[number].get()->UpdatePosition(vectorOfTanks[number].get()->GetMyPositionVector(), vectorOfTanks[number].get()->GetMyroration());
}

void GameObj::NextPlayer()
{
	int i = 0;
	while (!vectorOfTours[i]) //odnalezienie true
	{
		i++;
	}
		vectorOfTours[i] = false;
		vectorOfTanks[i].get()->SetCanMove(true);
		vectorOfTanks[i].get()->SetFrameCounter(0);
		vectorOfArtylery[i].get()->SetCanMove(true);

	if (i + 1 < vectorOfTours.size())
	{
		vectorOfTours[i + 1] = true;
	}
	else
	{
		vectorOfTours[0] = true;
	}

	wasArrowSet = false;
}

void GameObj::CheckTankBulletCollision()
{
	bool checkColision = false;
	int tmp = 0;

	for (auto &it : vectorOfTanks) //sprawdzenie wszystkich czolgow
	{
		if (it.get()->GetpositionX() >= bullet.get()->GetBuletPosVect().x - RADIUS && it.get()->GetpositionX() <= bullet.get()->GetBuletPosVect().x + RADIUS)
		{
			//zmienne zapisane w pamieci tymczasowo
			int tmpPositionX = it->GetpositionX();
			float tmpSize = it->GetMySize();
			float tmpPositionY = it->GetMyPositionVector().y;
			float tmpBulletX = bullet.get()->GetBuletPosVect().x;
			float tmpBulletY = bullet.get()->GetBuletPosVect().y;

			float tmpLD = sqrt(pow(abs((tmpPositionX - tmpSize*0.5f) - tmpBulletX), 2.f) + pow(abs(tmpPositionY - tmpBulletY), 2.f));
			float tmpLG = sqrt(pow(abs((tmpPositionX - tmpSize*0.5f) - tmpBulletX), 2.f) + pow(abs((tmpPositionY - tmpSize*0.5f) - tmpBulletY), 2.f));
			float tmpPD = sqrt(pow(abs((tmpPositionX + tmpSize*0.5f) - tmpBulletX), 2.f) + pow(abs(tmpPositionY - tmpBulletY), 2.f));
			float tmpPG = sqrt(pow(abs((tmpPositionX + tmpSize*0.5f) - tmpBulletX), 2.f) + pow(abs((tmpPositionY - tmpSize*0.5f) - tmpBulletY), 2.f));
			
			if (tmpLD <= RADIUS && !checkColision)
				checkColision = true;
			if (tmpLG <= RADIUS && !checkColision)
				checkColision = true;
			if (tmpPD <= RADIUS && !checkColision)
				checkColision = true;
			if (tmpPG <= RADIUS && !checkColision)
				checkColision = true;
			if (checkColision)
			{
				it.get()->SetHealth(50.f);
				uiInterface->SetDrawableHud(tmp);
			}
			checkColision = false;
		}
		tmp++;
	}
}

void GameObj::CheckTanksAlive()
{
	wasNextPlayer = false;

	for (int i=0; i<vectorOfTanks.size(); i++)
	{
		if (vectorOfTanks[i]->GetMyHealth() == 0)
		{
			if (vectorOfTours[i] == true)
			{
				NextPlayer();
				wasNextPlayer = true;
			}

			vectorOfTanks.erase(vectorOfTanks.begin() + i);
			vectorOfArtylery.erase(vectorOfArtylery.begin() + i);
			vectorOfTours.erase(vectorOfTours.begin() + i);
			uiInterface->DeleteHudAtPosition(i);
		}

		if (vectorOfTanks.size() == 1)
			isEndGame = true;
	}
}

void GameObj::LoadTextures()
{
	int error = 201;
	if (!tankTexture.loadFromFile("Prefabs/tank_40x40.png"))
		throw error;

	if (!backgroundTexture.loadFromFile("Prefabs/gameBackground_sand.png"))
		throw error;
}

void GameObj::MakeBackground()
{
	Vector2u textureSize;

	textureSize = backgroundTexture.getSize();
	float scaleX = (float)SCRNWIDTH / textureSize.x;
	float scaleY = (float)SCRNHEIGHT / textureSize.y;

	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(scaleX, scaleY);
}

void GameObj::DestroyBullet()
{
	//wykrycie kolizji z ziemia
	land.get()->DestroyArena(bullet.get()->GetBuletPosVect());
	CheckTankBulletCollision();
	CheckTanksAlive();
	bullet.reset();

	if (!wasNextPlayer)
		NextPlayer();
}

bool GameObj::IsTanksContainsBullet()
{
	bool tmp = false;

	for (auto &it : vectorOfTanks)
	{
		if (it->IsTankContains(bullet->GetBuletPosVect()))
			tmp = true;
	}

	return tmp;
}
