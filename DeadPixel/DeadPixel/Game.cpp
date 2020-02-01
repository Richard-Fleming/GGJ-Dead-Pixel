#include "Game.h"

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ s_screenWidth, s_screenHeight, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
	, m_currentLevel{ 1 }
{
	m_startCam = sf::Vector2f(800.0f, 600.0f);//should be set off player position
	levelLoader();
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	
	m_endCam = sf::Vector2f(1400.0f, 600.0f);//should be set off end position
	m_cameraSpeed = 1;//may be based off level
	m_gamePlayer.initialise();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		m_gamePlayer.processKeys(newEvent);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	moveCamera();//off while setting up
	m_gamePlayer.update(t_deltaTime);
	for (int i = 0; i < m_platforms.size(); i++)
	{
		m_platforms[i].playerContact(m_gamePlayer.hitBlock(m_platforms[i].getBody()), 
															m_gamePlayer.ColorArray[m_gamePlayer.colorNum]);
	}
	if (m_gamePlayer.getBody().getGlobalBounds().intersects(m_bucket.getGlobalBounds()))
	{
		m_currentLevel++;
		m_cameraSpeed++;
		m_platforms.clear();
		m_gamePlayer.initialise();
		levelLoader();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear();
	for (int i = 0; i < m_platforms.size(); i++)
	{
		m_platforms[i].draw(m_window);
	}
	m_gamePlayer.render(m_window);
	m_window.draw(m_bucket);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_bucketTexture.loadFromFile("ASSETS//IMAGES//bucket.png"))
	{
		std::cout << "Bucket's fucked up." << std::endl;
	}
	m_bucket.setTexture(m_bucketTexture);
	m_bucket.setPosition(m_platforms[3].getBody().getPosition().x - (m_bucket.getGlobalBounds().width / 2) + (m_platforms[3].getBody().getGlobalBounds().width / 2), 
						m_platforms[3].getBody().getPosition().y - m_bucket.getGlobalBounds().height);
}

void Game::moveCamera()
{
	sf::View tempView = m_window.getView();
	if (m_endCam.x > tempView.getCenter().x)
	{
		tempView.setCenter(tempView.getCenter().x + m_cameraSpeed, tempView.getCenter().y);
		m_window.setView(tempView);
	}
}

void Game::levelLoader()
{
	std::string line;
	std::ifstream levelFile("Levels//Level" + std::to_string(m_currentLevel) + ".txt");
	if (levelFile.is_open())
	{
		while (std::getline(levelFile, line))
		{
			std::cout << "Loading..." << std::endl;
			m_xPosString = line;
			m_xPosString.replace(4, 500, "");
			m_converter.str(m_xPosString);
			m_converter >> m_position.x;
			m_converter.clear();

			m_yPosString = line;
			m_yPosString.replace(0, 5, "");
			m_converter.str(m_yPosString);
			m_converter >> m_position.y;
			m_converter.clear();

			m_xSizeString = line;
			m_xSizeString.replace(0, 10, "");
			m_converter.str(m_xSizeString);
			m_converter >> m_size.x;
			m_converter.clear();

			m_ySizeString = line;
			m_ySizeString.replace(0, 14, "");
			m_converter.str(m_ySizeString);
			m_converter >> m_size.y;
			m_converter.clear();

			m_tempBlock.setUp(m_position, m_size);
			m_platforms.push_back(m_tempBlock);
		}
		levelFile.close();
	}
	
	sf::View tempView = m_window.getView();
	tempView.setCenter(m_startCam.x, tempView.getCenter().y);
	m_window.setView(tempView);

	m_bucket.setPosition(m_platforms[m_platforms.size() - 1].getBody().getPosition().x - (m_bucket.getGlobalBounds().width / 2) + (m_platforms[m_platforms.size() - 1].getBody().getGlobalBounds().width / 2),
		m_platforms[m_platforms.size() - 1].getBody().getPosition().y - m_bucket.getGlobalBounds().height);
	m_endCam.x = m_bucket.getPosition().x;
}
