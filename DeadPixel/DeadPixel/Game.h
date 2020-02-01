#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Block.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void levelLoader();
	Player m_gamePlayer;
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	int m_currentLevel;
	sf::Vector2f m_position;
	std::string m_xPosString;
	std::string m_yPosString;
	sf::Vector2f m_size;
	std::string m_xSizeString;
	std::string m_ySizeString;
	std::stringstream m_converter;
	Block m_tempBlock;
	std::vector<Block> m_platforms;

};

#endif // !GAME_HPP

