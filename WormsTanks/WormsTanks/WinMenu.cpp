#include "WinMenu.h"

WinMenu::WinMenu(const string &name) : playerName(name)
{
	isButtonPressed = false;
}

WinMenu::~WinMenu()
{
}

void WinMenu::LoadFromFile()
{
	int error = 301;

	if (!backgroundTexture.loadFromFile("Prefabs/win_backguround.png"))
		throw error;

	if (!menuButtonTexture.loadFromFile("Prefabs/menu_button.png"))
		throw error;

	if (!monsterratFont.loadFromFile("Prefabs/Montserrat-Bold.otf"))
		throw error;
}

void WinMenu::Initialize()
{
	backgroundTexture.setSmooth(true);
	backgroundShape.setSize(Vector2f(SCRNWIDTH, SCRNHEIGHT));
	backgroundShape.setTexture(&backgroundTexture);
	backgroundShape.setPosition(0.f, 0.f);

	menuButtonTexture.setSmooth(true);
	menuButtonShape.setSize(Vector2f(menuButtonTexture.getSize()));
	menuButtonShape.setTexture(&menuButtonTexture);
	menuButtonShape.setOrigin(menuButtonShape.getSize().x / 2.f, menuButtonShape.getSize().y / 2.f);
	menuButtonShape.setPosition(SCRNWIDTH / 2.f, SCRNHEIGHT - 100.f);

	playerNumber.setFont(monsterratFont);
	playerNumber.setString(playerName);
	playerNumber.setCharacterSize(WINSIZE);
	playerNumber.setOrigin(playerNumber.getLocalBounds().width / 2.f, playerNumber.getLocalBounds().height / 2.f);
	playerNumber.setFillColor(Color::Red);
	playerNumber.setPosition(SCRNWIDTH / 2.f, SCRNHEIGHT / 2.f);
}

void WinMenu::Draw(RenderWindow & w)
{
	w.draw(backgroundShape);
	w.draw(menuButtonShape);
	w.draw(playerNumber);
}

void WinMenu::Update(RenderWindow & w)
{
	CheckMenuButtonHover(w);
}

bool WinMenu::GetIsButtonPressed() const
{
	return isButtonPressed;
}

void WinMenu::CheckMenuButtonHover(const RenderWindow & w)
{
	if (menuButtonShape.getGlobalBounds().contains((Vector2f)Mouse::getPosition(w)))
	{
		menuButtonShape.setFillColor(Color(51, 51, 51, 180));
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			isButtonPressed = true;
		}
	}
	else
		menuButtonShape.setFillColor(Color(255, 255, 255, 255));
}
