#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
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
	void levelLoader(Block t_block);

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	int m_currentLevel;

};

#endif // !GAME_HPP

