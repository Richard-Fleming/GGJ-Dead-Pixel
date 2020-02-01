#include "Block.h"

Block::Block()
{
}

void Block::setUp(sf::Vector2f t_pos, sf::Vector2f t_size)
{
	m_body.setPosition(t_pos);
	m_body.setSize(t_size);
	m_body.setFillColor(GREY);
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
		m_body.setFillColor(t_playerColour);
	}
}
