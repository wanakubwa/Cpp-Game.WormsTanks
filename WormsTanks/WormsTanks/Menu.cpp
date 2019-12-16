#include "Menu.h"

Menu::Menu()
{
	isButtonPressed = false;
	landTypeEnum = LandType::hilly;
	playersEnum = PlayersNumber::two;
}

Menu::~Menu()
{
}

void Menu::LoadFromFile()
{
	int error = 101;

	if (!backgroundTexture.loadFromFile("Prefabs/background.png"))
		throw error;

	if (!playButtonTexture.loadFromFile("Prefabs/play_button.png"))
		throw error;

	if (!playersNumberTexture.loadFromFile("Prefabs/players.png"))
		throw error;

	if (!landTypeTexture.loadFromFile("Prefabs/land_type.png"))
		throw error;

	if (!twoPlayersTexture.loadFromFile("Prefabs/2_players.png"))
		throw error;

	if (!threePlayersTexture.loadFromFile("Prefabs/3_players.png"))
		throw error;

	if (!fourPlayersTexture.loadFromFile("Prefabs/4_players.png"))
		throw error;

	if (!hillyTexture.loadFromFile("Prefabs/hilly.png"))
		throw error;

	if (!flatTexture.loadFromFile("Prefabs/flat.png"))
		throw error;
}

void Menu::Initialize()
{
	backgroundTexture.setSmooth(true);
	backgroundSprite.setSize(Vector2f(SCRNWIDTH, SCRNHEIGHT));
	backgroundSprite.setTexture(&backgroundTexture);
	backgroundSprite.setPosition(0.f, 0.f);

	playButtonTexture.setSmooth(true);
	playButtonShape.setSize(Vector2f(375.f, 120.f));
	playButtonShape.setTexture(&playButtonTexture);
	playButtonShape.setOrigin(playButtonShape.getSize().x /2.f, playButtonShape.getSize().y / 2.f);
	playButtonShape.setPosition(SCRNWIDTH/2.f, SCRNHEIGHT - 100.f);

	landTypeTexture.setSmooth(true);
	landTypeShape.setSize(Vector2f(448.f, 80.f));
	landTypeShape.setTexture(&landTypeTexture);
	landTypeShape.setPosition(50.f, 350.f);

	playersNumberTexture.setSmooth(true);
	playersShape.setSize(Vector2f(playersNumberTexture.getSize().x, playersNumberTexture.getSize().y));
	playersShape.setTexture(&playersNumberTexture);
	playersShape.setPosition(landTypeShape.getPosition().x, landTypeShape.getPosition().y + landTypeShape.getGlobalBounds().height + 45.f);
	
	ListPlayersNumberInitialize();
	ListLandTypeInitialize();
}

void Menu::Draw(RenderWindow & w)
{
	w.draw(backgroundSprite);
	w.draw(playButtonShape);
	w.draw(landTypeShape);
	w.draw(playersShape);
	
	for (auto &it : listPlayerNum)
		w.draw(it);

	for (auto &it : listLandType)
		w.draw(it);
}

void Menu::Update(RenderWindow & w)
{
	CheckPlayButtonHover(w);
	CheckLandtypeHover(w);
	CheckPlayersNumberHover(w);
}

bool Menu::GetIsButtonPressed() const
{
	return isButtonPressed;
}

int Menu::GetPlayersNumber() const
{
	return playersEnum;
}

int Menu::GetLandType() const
{
	return landTypeEnum;
}

void Menu::ListPlayersNumberInitialize()
{
	RectangleShape twoPlayersShape;
	twoPlayersTexture.setSmooth(true);
	twoPlayersShape.setSize(Vector2f(twoPlayersTexture.getSize().x, twoPlayersTexture.getSize().y));
	twoPlayersShape.setTexture(&twoPlayersTexture);
	twoPlayersShape.setPosition(playersShape.getPosition().x + playersShape.getGlobalBounds().width + 35.f, playersShape.getPosition().y);
	listPlayerNum.push_back(twoPlayersShape); //kopia ksztaltu

	RectangleShape threePlayersShape;
	threePlayersTexture.setSmooth(true);
	threePlayersShape.setSize(Vector2f(threePlayersTexture.getSize().x, threePlayersTexture.getSize().y));
	threePlayersShape.setTexture(&threePlayersTexture);
	threePlayersShape.setPosition(twoPlayersShape.getPosition().x + twoPlayersShape.getGlobalBounds().width + 35.f, playersShape.getPosition().y);
	listPlayerNum.push_back(threePlayersShape); //kopia ksztaltu

	RectangleShape fourPlayersShape;
	fourPlayersTexture.setSmooth(true);
	fourPlayersShape.setSize(Vector2f(fourPlayersTexture.getSize().x, fourPlayersTexture.getSize().y));
	fourPlayersShape.setTexture(&fourPlayersTexture);
	fourPlayersShape.setPosition(threePlayersShape.getPosition().x + threePlayersShape.getGlobalBounds().width + 35.f, playersShape.getPosition().y);
	listPlayerNum.push_back(fourPlayersShape); //kopia ksztaltu
}

void Menu::ListLandTypeInitialize()
{
	RectangleShape hillyShape; //pos 0
	hillyTexture.setSmooth(true);
	hillyShape.setSize(Vector2f(hillyTexture.getSize().x, hillyTexture.getSize().y));
	hillyShape.setTexture(&hillyTexture);
	hillyShape.setPosition(landTypeShape.getPosition().x + landTypeShape.getGlobalBounds().width + 35.f, landTypeShape.getPosition().y);
	listLandType.push_back(hillyShape);

	RectangleShape flatShape; //pos 1
	flatTexture.setSmooth(true);
	flatShape.setSize(Vector2f(flatTexture.getSize().x, flatTexture.getSize().y));
	flatShape.setTexture(&flatTexture);
	flatShape.setPosition(hillyShape.getPosition().x + hillyShape.getGlobalBounds().width + 35.f, landTypeShape.getPosition().y);
	listLandType.push_back(flatShape);
}

void Menu::CheckPlayButtonHover(const RenderWindow & w)
{
	if (playButtonShape.getGlobalBounds().contains((Vector2f)Mouse::getPosition(w)))
	{
		playButtonShape.setFillColor(Color(51, 51, 51, 180));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			isButtonPressed = true;
		}
	}
	else
		playButtonShape.setFillColor(Color(255, 255, 255, 255));
}

void Menu::CheckLandtypeHover(const RenderWindow & w)
{
	Vector2f tmp = (Vector2f)Mouse::getPosition(w);
	int myCount = 0;
	for (auto &it : listLandType)
	{
		if (it.getGlobalBounds().contains(tmp))
		{
			it.setFillColor(Color(51, 51, 51, 180));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (myCount)
				{
				case 0:
					landTypeEnum = LandType::hilly;
					break;
				case 1:
					landTypeEnum = LandType::flat;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			if(myCount != landTypeEnum)
				it.setFillColor(Color::White);
			else
				it.setFillColor(Color(51, 51, 51, 180));
		}
		myCount++;
	}
}

void Menu::CheckPlayersNumberHover(const RenderWindow & w)
{
	Vector2f tmp = (Vector2f)Mouse::getPosition(w);
	int myCount = 2;
	for (auto &it : listPlayerNum)
	{
		if (it.getGlobalBounds().contains(tmp))
		{
			it.setFillColor(Color(51, 51, 51, 180));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				switch (myCount)
				{
				case 2:
					playersEnum = PlayersNumber::two;
					break;
				case 3:
					playersEnum = PlayersNumber::three;
					break;
				case 4:
					playersEnum = PlayersNumber::four;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			if (myCount != playersEnum)
				it.setFillColor(Color::White);
			else
				it.setFillColor(Color(51, 51, 51, 180));
		}
		myCount++;
	}
}
