#include "Player.h"
#include <ctime>
Player::Player()
{
}

Player::~Player()
{
}

void Player::initialise()
{
	srand(time(NULL));
	m_playerLocation = { 400,500 };
	m_playerVelocity = { 0,0 };
	m_player.setPosition(m_playerLocation);
	m_player.setSize(playerSize);
	m_player.setOrigin(playerSize.x/2,playerSize.y/2);
	m_player.setFillColor(ColorArray[0]);
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_player);
}

void Player::update(sf::Time t_deltaTime)
{
	movePlayer();
	slowPlayer();
	stopPlayer();
	fall();
	colorRandomiser();
}

void Player::processKeys(sf::Event t_newEvent)
{
	if (t_newEvent.type == sf::Event::KeyReleased)
	{
		if (sf::Keyboard::Space == t_newEvent.key.code )
		{
			jump();
		}
	}
	if (sf::Keyboard::D == t_newEvent.key.code)
	{
		right();
	}

	if (sf::Keyboard::A == t_newEvent.key.code )
	{
		left();

	}


}

void Player::movePlayer()
{
	m_playerLocation += m_playerVelocity;
	m_player.setPosition(m_playerLocation);
}

void Player::stopPlayer()
{
	if (m_playerLocation.x <= 10)
	{
		m_playerVelocity = { 0,0 };
	}
	if (m_playerLocation.x >= 790)
	{
		m_playerVelocity = { 0,0 };
	}
	if (m_playerLocation.y >= 580)
	{
		m_playerVelocity.y = 0;
		m_playerLocation.y = 580;
	}
}

void Player::slowPlayer()
{
	
	
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_playerVelocity.x *= 0.95;
		}
	

	if (m_playerVelocity.x < 0.2 && m_playerVelocity.x > -0.2)
	{
		m_playerVelocity.x = 0;
	}
	if (m_playerLocation.x > 780)
	{
		m_playerLocation.x = 780;
	}
	if (m_playerLocation.x < 10)
	{
		m_playerLocation.x = 10;
	}
}

void Player::jump()
{
	m_playerVelocity += Jumppower;
}

void Player::left()
{
	if (m_playerLocation.x > 10)
	{
		if(m_playerVelocity.x < 7 && m_playerVelocity.x > -7)
		m_playerVelocity.x  = -5;
	}




}

void Player::right()
{
	if (m_playerLocation.x < 780)
	{
		if (m_playerVelocity.x < 7 && m_playerVelocity.x > -7)
			m_playerVelocity.x = 5;
	}


}

void Player::fall()
{
	if (m_playerVelocity.y < 15 )
	{
		m_playerVelocity += gravity;
	}
}

void Player::colorRandomiser()
{
	
	TimeSinceLastColor += colorClock.restart();
	int colorNum = 0;
	if (TimeSinceLastColor > sf::seconds(3))
	{
		colorNum = rand() % 6;
		m_player.setFillColor(ColorArray[colorNum]);
		TimeSinceLastColor = sf::seconds(0);
	}
	


}
