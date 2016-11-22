#include "Game.h"
#include "CollisionDetector.h"

/// <summary>
/// @author RP
/// @date June 2016
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;


/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game()

 
: m_window(sf::VideoMode(1440, 900, 32), "SFML Playground", sf::Style::Default)

{	
	m_window.setVerticalSyncEnabled(true);
	int currentLevel = 1;

	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;
	}


	
	if (!m_bgTexture.loadFromFile(m_level.m_background.m_fileName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	//m_sprite.setPosition(m_level.m_tank.m_position.x, m_level.m_tank.m_position.y);
	
	m_bgSprite.setTexture(m_bgTexture);
	
	//m_sprite.setTexture(m_texture);
	//m_sprite.setOrigin(m_texture.getSize().x / 2.0, m_texture.getSize().y / 2.0);
	//m_sprite.setRotation(270);
	//m_sprite.rotate(90);

	sf::Sprite sprite;
	sprite.setTexture(m_texture);
	
	/*for (auto &obstacle : m_level.m_obstacles)
	{
		sprite.setPosition(obstacle.m_position);
		sprite.rotate(obstacle.m_rotation);
		m_sprites.push_back(sprite);
	}*/

	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	m_tank.reset(new Tank(m_texture, m_level.m_tank.m_position, m_keyHandler));
	generateWalls();
}



/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);
	// Create the Walls 
	for (ObstacleData const &obstacle : m_level.m_obstacles)
	{
		std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
		sprite->setTexture(m_texture);
		sprite->setTextureRect(wallRect);
		sprite->setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite->setPosition(obstacle.m_position);
		sprite->setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(std::move(sprite));
	}
}
bool Game::checkTankWallCollision()
{
	for (std::unique_ptr<sf::Sprite> const & sprite : m_wallSprites)
	{
		if (CollisionDetector::collision(m_tank->getTurretSprite(), *sprite))
		{
			m_tank->stop();
			return true;
			
		}
		if (CollisionDetector::collision(m_tank->getBaseSprite(), *sprite))
		{
			m_tank->stop();
			return true;
			
		}
	}
	return false;
}
/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{
	

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			m_keyHandler.updateKey(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			m_keyHandler.updateKey(event.key.code, false);
			break;
		default:
			break;
		}


	}
	


/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	m_tank->update(dt);
	checkTankWallCollision();
	
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_bgSprite);
	m_tank->render(m_window);
	
	
	for (auto &m_sprite : m_wallSprites)
	{
		m_window.draw(*m_sprite);

	}
	m_window.display();
}



