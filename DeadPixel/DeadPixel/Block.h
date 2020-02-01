#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
	sf::Color GREY = sf::Color(100, 100, 100);

	Block();
	void setUp(sf::Vector2f t_pos, sf::Vector2f t_size);
	void draw(sf::RenderWindow& t_window);

	sf::RectangleShape getBody();
	void playerContact(bool t_contact, sf::Color t_playerColour);

private:
	sf::RectangleShape m_body;
};

