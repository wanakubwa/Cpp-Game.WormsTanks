#include "UI.h"

UI::UI()
{
	isArrowDrawable = false;
	arrowFrameLimit = 120;
	arrowVelocity = Vector2f(0.f, 1.f);
}

UI::~UI()
{
}

void UI::LoadFromFile()
{
	int error = 202;
	if (!arrowTexture.loadFromFile("Prefabs/arrow_40x30.png"))
	{
		throw error;
	}

	if (!font.loadFromFile("Prefabs/Montserrat-Bold.otf"))
	{
		throw error;
	}
}

void UI::Initialize(const int numberOfPlayers)
{
	backgroundShape.setSize(Vector2f(SCRNWIDTH, UIHEIGHT));
	backgroundShape.setPosition(Vector2f(0.f, 0.f));
	backgroundShape.setFillColor(Color::Color(139, 171, 191));

	barOfPower.setSize(Vector2f(300.f, 25.f));
	barOfPower.setOrigin(barOfPower.getSize().x*0.5f, barOfPower.getSize().y*0.5f);
	barOfPower.setOutlineThickness(-2.f);
	barOfPower.setOutlineColor(Color::Color(56, 58, 99));
	barOfPower.setPosition(backgroundShape.getLocalBounds().width*0.5f, backgroundShape.getLocalBounds().height*0.5f);

	playerArrow.setTexture(&arrowTexture);
	playerArrow.setSize(Vector2f(arrowTexture.getSize()));
	playerArrow.setOrigin(playerArrow.getSize().x / 2.f, playerArrow.getSize().y / 2.f);

	for (int i = 0; i < numberOfPlayers; i++)
	{
		playerHudArena.push_back(OnePlayerHud(to_string(i+1), font));
	}

	BarInitialize();
}

void UI::UpdateUi(float powerOfShot, int maxPower)
{
	
	if (powerOfShot != 0.f)
	{
		float tmp = powerOfShot / maxPower; //procent wypelnienia
		(*(barAnimation.get()))[2].position = Vector2f((*(barAnimation.get()))[1].position.x + barOfPower.getLocalBounds().width*tmp, barOfPower.getPosition().y - barOfPower.getLocalBounds().height*0.5f);
		(*(barAnimation.get()))[3].position = Vector2f((*(barAnimation.get()))[1].position.x + barOfPower.getLocalBounds().width*tmp, barOfPower.getPosition().y + barOfPower.getLocalBounds().height*0.5f);
	}
	else
	{
		(*(barAnimation.get()))[2].position = Vector2f(barOfPower.getPosition().x - barOfPower.getLocalBounds().width*0.5f, barOfPower.getPosition().y - barOfPower.getLocalBounds().height*0.5f);
		(*(barAnimation.get()))[3].position = Vector2f(barOfPower.getPosition().x - barOfPower.getLocalBounds().width*0.5f, barOfPower.getPosition().y + barOfPower.getLocalBounds().height*0.5f);
	}
}

void UI::Draw(RenderWindow & w)
{
	for (auto &it : playerHudArena)
	{
		if (it.isDrawable)
			it.DrawHud(w);
	}

	if(isArrowDrawable)
		w.draw(playerArrow);

	w.draw(backgroundShape);
	w.draw(barOfPower);
	w.draw(*(barAnimation.get()));
}

void UI::BarInitialize()
{
	barAnimation = make_unique<VertexArray>(TrianglesStrip, 4);
	(*(barAnimation.get()))[0].position = Vector2f(barOfPower.getPosition().x - barOfPower.getLocalBounds().width*0.5f, barOfPower.getPosition().y - barOfPower.getLocalBounds().height*0.5f);
	(*(barAnimation.get()))[1].position = Vector2f(barOfPower.getPosition().x - barOfPower.getLocalBounds().width*0.5f, barOfPower.getPosition().y + barOfPower.getLocalBounds().height*0.5f);
	(*(barAnimation.get()))[2].position = Vector2f(barOfPower.getPosition().x - barOfPower.getLocalBounds().width*0.5f, barOfPower.getPosition().y - barOfPower.getLocalBounds().height*0.5f);
	(*(barAnimation.get()))[3].position = Vector2f(barOfPower.getPosition().x - barOfPower.getLocalBounds().width*0.5f, barOfPower.getPosition().y + barOfPower.getLocalBounds().height*0.5f);

	(*(barAnimation.get()))[0].color = Color::Color(138, 0, 71);
	(*(barAnimation.get()))[1].color = Color::Color(138, 0, 71);
	(*(barAnimation.get()))[2].color = Color::Color(138, 0, 71);
	(*(barAnimation.get()))[3].color = Color::Color(138, 0, 71);
}

void UI::DeleteHudAtPosition(int i)
{
	playerHudArena.erase(playerHudArena.begin() + i);
}

void UI::PlayArrowAt(const Vector2f & position)
{
	isArrowDrawable = true;
	playerArrow.setPosition(position.x, position.y - 100.f);
}

string UI::GetPlayerName() const
{
	string tmp = playerHudArena.front().nickName.getString();
	return tmp;
}

void UI::UpdateHudPosition(int position, Vector2f newPosition, float rotation, float hp, RenderWindow & w)
{
	float tmp = 40.f * 0.01f; //wielkosc w px jednej jednostki hp w odniesieniu do wielkosci paska (dlugosc_paska * 1/ilosc hp)

	playerHudArena[position].playerHudHitbox.setPosition(newPosition);
	playerHudArena[position].playerHudHitbox.setRotation(rotation);

	playerHudArena[position].playerHealthBarHov.setPosition(playerHudArena[position].playerHudHitbox.getPosition().x, playerHudArena[position].playerHudHitbox.getPosition().y - 45.f);

	playerHudArena[position].playerHealthBar.setPosition(playerHudArena[position].playerHudHitbox.getPosition().x, playerHudArena[position].playerHudHitbox.getPosition().y - 45.f);
	playerHudArena[position].playerHealthBar.setSize(Vector2f(tmp*hp, playerHudArena[position].playerHealthBar.getSize().y));

	playerHudArena[position].nickName.setPosition(playerHudArena[position].playerHealthBar.getPosition().x, playerHudArena[position].playerHealthBar.getPosition().y - 20.f);

	
	if (CheckMouseCollision(playerHudArena[position].playerHudHitbox, w))
	{
		SetDrawableHud(position);
		playerHudArena[position].frameCounter = 0;
	}
		
}

void UI::SetDrawableHud(int number)
{
	playerHudArena[number].isDrawable = true;
	playerHudArena[number].frameCounter = 0;
}

void UI::SetIsArrowDrawable(bool value)
{
	isArrowDrawable = value;
}

bool UI::CheckMouseCollision(const RectangleShape &shape, RenderWindow & w)
{
	if(shape.getGlobalBounds().contains((Vector2f)Mouse::getPosition(w)))
		return true;
	return false;
}

UI::OnePlayerHud::OnePlayerHud(const string &name, const Font &f)
{
	playerHudHitbox.setFillColor(Color::Transparent);
	playerHudHitbox.setOutlineThickness(1.f);
	playerHudHitbox.setOutlineColor(Color::Black);
	playerHudHitbox.setSize(Vector2f(35.f, 35.f));
	playerHudHitbox.setOrigin(playerHudHitbox.getSize().x*0.5f, playerHudHitbox.getSize().y);

	playerHealthBar.setFillColor(Color::Red);
	playerHealthBar.setSize(Vector2f(40.f, 10.f));
	playerHealthBar.setOrigin(playerHealthBar.getSize().x*0.5f, playerHealthBar.getSize().y*0.5f);

	playerHealthBarHov.setFillColor(Color::White);
	playerHealthBarHov.setSize(Vector2f(40.f, 10.f));
	playerHealthBarHov.setOrigin(playerHealthBar.getSize().x*0.5f, playerHealthBar.getSize().y*0.5f);

	nickName.setFont(f);
	nickName.setString(name);
	nickName.setCharacterSize(10.f);
	nickName.setOrigin(nickName.getGlobalBounds().width*0.5f, nickName.getGlobalBounds().height*0.5f);

	isDrawable = false;
	frameCounter = 0;
	frameLimit = 1000;
}

void UI::OnePlayerHud::DrawHud(RenderWindow & w)
{
	if (frameCounter < frameLimit)
	{
		w.draw(playerHealthBarHov);
		w.draw(playerHealthBar);
		w.draw(nickName);
		frameCounter++;
	}
	else
	{
		isDrawable = false;
	}
}
