#include "Game.h"
#include "CollisionDetector.h"

/// <summary>
/// @author Aaron Curry
/// @date 0/12/2016
/// @id C00202505
/// @version 1.0
/// @timeTaken approximately 31 hours
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

{	//cap to 60fps
	m_window.setVerticalSyncEnabled(true);
	//Assing variables initial values
	int currentLevel = 1;
	countDown = 60;
	score = 0;
	highScore = 0;
	m_ss << countDown;
	m_sScore << score;
	m_sHighScore << accuracy;
	


	

	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;
	}

	//Loading in images as texture assigning them to sprites 
	
	if (!m_bgTexture.loadFromFile(m_level.m_background.m_fileName))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}
	
	
	m_bgSprite.setTexture(m_bgTexture);
	
	sf::Sprite sprite;
	sprite.setTexture(m_texture);
	

	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	sf::Sprite target;
	target.setTexture(m_texture2);
	//Loading in target image
	if(!m_texture2.loadFromFile("./resources/images/target.png"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	//Load font
	m_font.loadFromFile("C:/windows/fonts/times.ttf");
	m_text.setFont(m_font);
	m_timeText.setFont(m_font);
	m_scoreText.setFont(m_font);
	m_GameOver.setFont(m_font);
	m_score.setFont(m_font);
	m_restart.setFont(m_font);
	m_highScoreText.setFont(m_font);
	m_highScore.setFont(m_font);
	m_accuracy.setFont(m_font);
	m_accuracyText.setFont(m_font);
	
	m_tank.reset(new Tank(m_texture, m_level.m_tank.m_position, m_keyHandler));
	m_target.reset(new Target(m_texture2, m_level.m_target.m_position, m_keyHandler));
	
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
//Checks tank collision with tank by using the sprite rectangles
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
//Checks bullet collision with target by using the sprite rectangles
bool Game::checkBulletTargetCollision()
{
	if (m_tank->bulletAlive == true && CollisionDetector::collision(m_tank->getBulletSprite(), m_target->getTargetSprite()))
	{
		m_tank->bulletAlive = false;
		m_target->hit = true;
		if (m_target->hit = true)
		{
			targetHit++;
			score++;
			m_target->hit = false;

			m_sScore.str("");
			m_sScore << score;
			//std::cout << "score" << std::endl;
			m_target.reset(new Target(m_texture2, m_level.m_target.m_position, m_keyHandler));
		}
		

	
			return true;
	}
}
//Checks bullet collision with wall by 
bool Game::checkBulletWallCollision()
{
	for (std::unique_ptr<sf::Sprite> const & sprite : m_wallSprites)
	{
		if (CollisionDetector::collision(m_tank->getBulletSprite(), *sprite))
		{
			m_tank->bulletAlive = false;;
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

//Method to detect key presses to restart or quit the game
void Game::handleKeyInput()
{
	if (m_keyHandler.isPressed(sf::Keyboard::Key::Escape))
	{
		m_window.close();
	}
	//Resest game variables
	if (countDown <=0 && m_keyHandler.isPressed(sf::Keyboard::Key::R))
	{
		score = 0;

		m_sScore.str("");
		m_sScore << score;

		countDown = 60;

		m_level.m_tank.m_position;
		m_tank->m_speed = 0;
	}
}


/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	handleKeyInput();
	//	GamePlay is updated when the timer is above 0
	if (countDown >= 0)
	{
		m_tank->update(dt);
		m_target->update(dt);
		checkTankWallCollision();
		checkBulletTargetCollision();
		checkBulletWallCollision();
	}
		
		m_timeSinceLastUpdate += m_clock.restart().asMilliseconds();

	if (m_timeSinceLastUpdate > 1000)
	{
		// reset time passed
		
		// decrement seconds timer
		m_timeSinceLastUpdate = 0;
		countDown--;
		std::cout << countDown << std::endl;

		m_ss.str("");
		m_ss << countDown;

	}
	//Simple code for setting the highscore
	if (score > highScore)
	{
		highScore = score;

		m_sHighScore.str("");
		m_sHighScore << highScore;
	}

	if (m_tank->shots > 0)
	{
		accuracy = (targetHit / m_tank->shots) * 100;
		m_sAccuracy.str("");
		m_sAccuracy << accuracy;
	}
	
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
	m_target->render(m_window);
	m_tank->render(m_window);
	
	
	for (auto &m_sprite : m_wallSprites)
	{
		m_window.draw(*m_sprite);

	
	}
	//Text objects are drawn when the game is playing
		m_highScoreText.setString(":HIGHSCORE:");
		m_highScoreText.setPosition(625, 20);
		m_highScoreText.setScale(1, 1);
		m_highScoreText.setColor(sf::Color::White);
		m_window.draw(m_highScoreText);

		m_highScore.setString(m_sHighScore.str());
		m_highScore.setPosition(710, 50);
		m_highScore.setScale(1, 1);
		m_highScore.setColor(sf::Color::Green);
		m_window.draw(m_highScore);
	
		m_score.setString(":SCORE");
		m_score.setPosition(1300, 20);
		m_score.setScale(1, 1);
		m_score.setColor(sf::Color::Black);
		m_window.draw(m_score);
	
		m_scoreText.setString(m_sScore.str());
		m_scoreText.setPosition(1250, 20);
		m_scoreText.setScale(1, 1);
		m_scoreText.setColor(sf::Color::Red);
		m_window.draw(m_scoreText);

		m_timeText.setString("TIME:");
		m_timeText.setPosition(20, 20);
		m_timeText.setColor(sf::Color::Black);
		m_window.draw(m_timeText);

		m_text.setString(m_ss.str());
		m_text.setPosition(130, 20);
		m_text.setColor(sf::Color::Blue);
		m_window.draw(m_text);


		/*m_accuracy.setString("accuracy");
		m_highScoreText.setPosition(800, 800);
		m_highScoreText.setScale(1, 1);
		m_highScoreText.setColor(sf::Color::White);
		m_window.draw(m_highScoreText);*/
		
		/*m_accuracy.setString(m_sAccuracy.str());
		m_accuracy.setPosition(800, 800);
		m_text.setColor(sf::Color::Blue);
		m_window.draw(m_accuracy);*/

		//Window cleared to white and Text objects drawn for the end screen
		if (countDown < 0)
		{

			m_window.clear(sf::Color(255,255,255,0));

			m_GameOver.setString("GAME OVER");
			m_GameOver.setPosition(525, 400);
			m_GameOver.setScale(2.5, 2.5);
			m_GameOver.setColor(sf::Color::Blue);
			m_window.draw(m_GameOver);
			
			m_accuracyText.setString("Accuracy:" + m_sAccuracy.str() + "%");
			m_accuracyText.setPosition(525, 550);
			m_accuracyText.setScale(1.5, 1.5);
			m_accuracyText.setColor(sf::Color::Black);
			m_window.draw(m_accuracyText);

			m_scoreText.setString(m_sScore.str());
			m_scoreText.setPosition(700, 250);
			m_scoreText.setScale(2, 2);
			m_scoreText.setColor(sf::Color::Red);
			m_window.draw(m_scoreText);

			m_score.setString("SCORE:");
			m_score.setPosition(525, 260);
			m_score.setScale(1.5, 1.5);
			m_score.setColor(sf::Color::Black);
			m_window.draw(m_score);

			m_restart.setString("press 'R' to restart");
			m_restart.setPosition(525, 660);
			m_restart.setScale(1, 1);
			m_restart.setColor(sf::Color::Red);
			m_window.draw(m_restart);

			m_highScoreText.setString("HIGHSCORE:");
			m_highScoreText.setPosition(525, 130);
			m_highScoreText.setScale(1.5, 1.5);
			m_highScoreText.setColor(sf::Color::Black);
			m_window.draw(m_highScoreText);

			m_highScore.setString(m_sHighScore.str());
			m_highScore.setPosition(800, 120);
			m_highScore.setScale(2, 2);
			m_highScore.setColor(sf::Color::Green);
			m_window.draw(m_highScore);

			
	    }
		//Game closes after 7 seconds
		if (countDown == -7)
		{
			m_window.close();
		}

	
	 m_window.display();
}



