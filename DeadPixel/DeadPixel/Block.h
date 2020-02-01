#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
	sf::Color GREY = sf::Color(100, 100, 100);
	const float TIME = 20.0f;
	Block();
	void setUp(sf::Vector2f t_pos, sf::Vector2f t_size);
	void update();
	void draw(sf::RenderWindow& t_window);

	sf::RectangleShape getBody();
	void playerContact(bool t_contact, sf::Color t_playerColour);

private:
	sf::RectangleShape m_body;
	sf::Vector3f colourDif;
	int time;
	sf::Texture blockTexture;
};

