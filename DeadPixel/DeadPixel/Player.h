#pragma once
#include <SFML\Graphics.hpp>
#include "ScreenSize.h"

class Player
{
public:
	Player();
	~Player();
	void initialise();
	void render(sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
	void processKeys(sf::Event t_newEvent);
	void movePlayer();
	void stopPlayer();
	void slowPlayer();
	void jump();
	void left();
	void right();
	void fall();
	void colorRandomiser();
	bool hitBlock(sf::RectangleShape t_block);



protected:
	bool APressed{ false };
	bool DPressed{ false };
	int spacePressed{ 0 };
	const sf::Vector2f playerSize{ 20.0f,20.0f };
	const sf::Vector2f Jumppower{ 0,-50 };
	const sf::Vector2f gravity{ 0,3 };
	sf::RectangleShape m_player;
	sf::Clock colorClock;
	sf::Time TimeSinceLastColor;
	sf::Vector2f m_playerLocation;
	sf::Vector2f m_playerVelocity;
	sf::Color ColorArray[6] = { sf::Color::Blue,sf::Color::Green,sf::Color::Red,sf::Color::Magenta,sf::Color::Yellow,sf::Color::Cyan };



};

