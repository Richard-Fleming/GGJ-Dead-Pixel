#include "Block.h"

Block::Block()
{
	time = TIME;
}

void Block::setUp(sf::Vector2f t_pos, sf::Vector2f t_size)
{
	m_body.setPosition(t_pos);
	m_body.setSize(t_size);
	m_body.setFillColor(GREY);
	colourDif = sf::Vector3f(0,0,0);

	if (!blockTexture.loadFromFile("ASSETS//IMAGES//block.png"))
	{
	}
	m_body.setTexture(&blockTexture);
}

void Block::update()
{
	if (time < TIME)
	{
		m_body.setFillColor(sf::Color(m_body.getFillColor().r + colourDif.x, m_body.getFillColor().g + colourDif.y, m_body.getFillColor().b + colourDif.z));
		time++;
	}
}



void Block::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

sf::RectangleShape Block::getBody()
{
	return m_body;
}

void Block::playerContact(bool t_contact, sf::Color t_playerColour)
{
	if (m_body.getFillColor() == GREY && t_contact)
	{
		colourDif = sf::Vector3f(t_playerColour.r - GREY.g, t_playerColour.g - GREY.r, t_playerColour.b - GREY.b);
		colourDif = sf::Vector3f(colourDif.x/TIME, colourDif.y / TIME, colourDif.z / TIME);
		time = 0;
	}
}
