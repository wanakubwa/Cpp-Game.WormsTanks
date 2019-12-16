#include "LevelMenager.h"

LevelMenager::LevelMenager()
{
	levelType = 0;
	levelTypeCounter = 0;
	playersNumber = 2;
	keyCode = 0; //bezruch na starcie
	errorCheck = false;

	window = make_unique<RenderWindow>(sf::VideoMode(SCRNWIDTH, SCRNHEIGHT), "WORMSO-CZOLGI");
}

LevelMenager::~LevelMenager()
{
	DestroyObjects();
}

void LevelMenager::Initialize()
{
	levelTypeCounter = levelType;

	switch (levelType)
	{
	case 0:
		MakeMenu();
		break;
	case 1:
		MakeMainGame();
		break;
	case 2:
		MakeWinMenu();
	default:
		break;
	}
}

void LevelMenager::RunGame()
{
	Initialize();
	Update();
}

void LevelMenager::Update()
{
	while (window->isOpen())
	{
		// Process events
		sf::Event event;
		
		//sprawdzenie kolejnej sceny
		CheckNextScene();
		if (errorCheck)
		{
			event.type = Event::Closed;
		}
			
		while (window->pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window->close();

			CheckKeyCode(event);
		}//end while
		
		 // Clear screen
		window->clear();

		switch (levelType)
		{
		case 0:
			menuObj->Update(*window);
			break;
		case 1:
			gameObj->RefreshGameObj(keyCode, *window);
			break;
		case 2:
			winMenuObj->Update(*window);
		default:
			break;
		}

		keyCode = 0;

		//przygotowanie klatki
		Draw();

		// Update the window
		window->display();
	}
}

void LevelMenager::Draw()
{
	switch (levelType)
	{
	case 0:
		menuObj->Draw(*window);
		break;
	case 1:
		gameObj->Draw(*window);
		break;
	case 2:
		winMenuObj->Draw(*window);
	default:
		break;
	}
}

void LevelMenager::MakeMainGame()
{
	gameObj = make_unique<GameObj>(playersNumber, landType);
	
	try
	{
		gameObj->LoadFromFile();
	}
	catch (...)
	{
		errorCheck = true;
	}

	if (!errorCheck)
	{
		gameObj->Initialize();
	}
}

void LevelMenager::MakeMenu() //obdluga wyjatkow
{
	menuObj = make_unique<Menu>();

	try
	{
		menuObj->LoadFromFile();
	}
	catch (...)
	{
		errorCheck = true;
	}

	if (!errorCheck)
	{
		menuObj->Initialize();
	}
}

void LevelMenager::MakeWinMenu()
{
	winMenuObj = make_unique<WinMenu>(playerName);

	try
	{
		winMenuObj->LoadFromFile();
	}
	catch (...)
	{
		errorCheck = true;
	}

	if (!errorCheck)
	{
		winMenuObj->Initialize();
	}
}

void LevelMenager::CheckNextScene()
{
	//klikniecie w guzik na menu
	if(menuObj)
		if (menuObj->GetIsButtonPressed())
		{
			levelType = 1;
			playersNumber = menuObj->GetPlayersNumber();
			landType = menuObj->GetLandType();
			menuObj.reset();
		}
		
	//spelnienie warunku konca gry
	if(gameObj)
		if (gameObj->IsEndGame())
		{
			levelType = 2;
			playerName = gameObj->GetplayerName();
			gameObj.reset();
		}
			
	//klikniecie w guzik winmenu
	if(winMenuObj)
		if (winMenuObj->GetIsButtonPressed())
		{
			levelType = 0;
			winMenuObj.reset();
		}

	if (levelType != levelTypeCounter)
		Initialize();
}

void LevelMenager::CheckKeyCode(Event &ev)
{
	if (ev.type == Event::KeyPressed)
	{
		switch (ev.key.code)
		{
		case Keyboard::A:
			keyCode = 2;
			break;
		case Keyboard::D:
			keyCode = 1;
			break;
		case Keyboard::Up:
			keyCode = 3;
			break;
		case Keyboard::Down:
			keyCode = 4;
			break;
		case Keyboard::Space:
			keyCode = 5;
			break;
		default:
			keyCode = 0;
			break;
		}//end switch
	}//end if

	if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::Space)
	{
		keyCode = 6; //release space key
	}
}

void LevelMenager::DestroyObjects()
{
	if (gameObj)
		gameObj.reset();

	else if (menuObj)
		menuObj.reset();
}
