#include "Player.h"
#include <ctime>
Player::Player()
{
	m_player.setFillColor(ColorArray[0]);
}

Player::~Player()
{
}

void Player::initialise()
{
	srand(time(NULL));
	playerState = true;
	m_playerLocation = { 150, 100 };
	m_playerVelocity = { 0,0 };
	m_player.setPosition(m_playerLocation);
	m_player.setSize(playerSize);
	m_player.setOrigin(playerSize.x/2,playerSize.y/2);
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
	colorChanger();
}

void Player::processKeys(sf::Event t_newEvent)
{
	if (t_newEvent.type == sf::Event::KeyReleased)
	{
		if (sf::Keyboard::Space == t_newEvent.key.code || sf::Keyboard::Up == t_newEvent.key.code)
		{
			
			spacePressed++;
			if (spacePressed < 3)
			{
				jump();
			}
		}
	}
}

void Player::movePlayer()
{
	m_playerLocation += m_playerVelocity;
	m_player.setPosition(m_playerLocation);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		right();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		left();
	}
}

void Player::stopPlayer()
{
	if (m_playerLocation.x <= 10)
	{
		m_playerVelocity = { 0,0 };
	}

	if (m_playerLocation.y >= s_screenHeight-20)
	{
		/*m_playerVelocity.y = 0;
		spacePressed = 0;
		m_playerLocation.y = s_screenHeight-20;*/
		playerState = false;

	}
}

void Player::slowPlayer()
{
	
	
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_playerVelocity.x *= 0.95;
		}
	

	if (m_playerVelocity.x < 0.2 && m_playerVelocity.x > -0.2)
	{
		m_playerVelocity.x = 0;
	}
	if (m_playerLocation.x < 10)
	{
		m_playerLocation.x = 10;
	}
}

void Player::jump()
{
	if (spacePressed == 1)
	{
		m_playerVelocity.y = 0;
		m_playerVelocity.y += Jumppower.y;
	}
	else if (spacePressed == 2)
	{
		if (m_playerVelocity.y > 0)
		{
			m_playerVelocity.y = 0;
		}
		m_playerVelocity.y += (Jumppower.y / 1.5);
	}
}

void Player::left()
{
	if (m_playerVelocity.x > 0)
	{
		m_playerVelocity.x = 0;
	}
	if (m_playerLocation.x > 10)
	{
		if (m_playerVelocity.x < 7 && m_playerVelocity.x > -7)
		{
			m_playerVelocity.x += -0.5;
		}
	}
}

void Player::right()
{
	if (m_playerVelocity.x < 0)
	{
		m_playerVelocity.x = 0;
	}
	if (m_playerVelocity.x < 7 && m_playerVelocity.x > -7)
			m_playerVelocity.x += 0.5;
}

void Player::fall()
{
	if (m_playerVelocity.y < 15 )
	{
		m_playerVelocity += gravity;
	}
}

void Player::colorChanger()
{
	TimeSinceLastColor += colorClock.restart();
	if (TimeSinceLastColor > sf::seconds(2))
	{
		colorNum++;
		if (colorNum >= 6)
		{
			colorNum = 0;
		}
		m_player.setFillColor(ColorArray[colorNum]);
		TimeSinceLastColor = sf::seconds(0);
	}

}

sf::RectangleShape Player::getBody()
{
	return m_player;
}

bool Player::hitBlock(sf::RectangleShape t_block)
{
	if (m_player.getGlobalBounds().intersects(t_block.getGlobalBounds()))
	{
		sf::RectangleShape tempPlayer = m_player;
		tempPlayer.move(-m_playerVelocity.x,0);
		if (!tempPlayer.getGlobalBounds().intersects(t_block.getGlobalBounds()))
		{
			if (m_playerVelocity.x > 0)
			{
				m_player.setPosition(t_block.getPosition().x - (playerSize.y / 2), m_player.getPosition().y);
				m_playerLocation.x = m_player.getPosition().x;
				m_playerVelocity.x = 0;
				return true;
			}
			else if (m_playerVelocity.x < 0)
			{
				m_player.setPosition(t_block.getPosition().x + t_block.getGlobalBounds().width + (playerSize.y / 2), m_player.getPosition().y);
				m_playerLocation.x = m_player.getPosition().x;
				m_playerVelocity.x = 0;
				return true;
			}
		}
		else
		{

			if (m_player.getPosition().y + (playerSize.y / 2) > t_block.getPosition().y&& m_playerVelocity.y > 0)
			{
				m_player.setPosition(m_player.getPosition().x, t_block.getPosition().y - (playerSize.y / 2));
				m_playerLocation.y = m_player.getPosition().y;
				m_playerVelocity.y = 0;
				spacePressed = 0;
				return true;
			}
			else if (m_player.getPosition().y - (playerSize.y / 2) < t_block.getPosition().y + t_block.getSize().y && m_playerVelocity.y < 0)
			{
				m_player.setPosition(m_player.getPosition().x, t_block.getPosition().y + t_block.getSize().y + (playerSize.y / 2));
				m_playerLocation.y = m_player.getPosition().y;
				m_playerVelocity.y = 0;
				return true;
			}
		}
	}

	return false;
}
