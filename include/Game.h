#pragma once

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
#include "Target.h"
#include "Tank.h"
#include "KeyHandler.h"



/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>
class Game
{
	// Load the game level data.
	LevelData m_level;
public:
	Game();	
	void run();
protected:	
	void update(double dt);
	void render();
	void processEvents();	
	void processGameEvents(sf::Event&);
	void generateWalls();
	void handleKeyInput();
	
	bool checkTankWallCollision();
	bool checkBulletTargetCollision();
	bool checkBulletWallCollision();
	
	// main window
	sf::RenderWindow m_window;
	sf::Sprite m_sprite;
	sf::Sprite m_bgSprite;
	
	sf::Texture m_bgTexture;
	
	sf::Texture m_texture;
	sf::Texture m_texture2;
	std::vector<sf::Sprite>  m_sprites;
	std::unique_ptr<Tank> m_tank;
	std::unique_ptr<Target> m_target;
	//std::unique_ptr<Target> m_bullet;
	
	std::string timerValue;
	// A container for the Wall sprites
	std::vector<std::unique_ptr<sf::Sprite>> m_targetSprites;
	std::vector<std::unique_ptr<sf::Sprite>> m_wallSprites;
	KeyHandler m_keyHandler;
	sf::Clock m_clock;
	double m_timeSinceLastUpdate;
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_scoreText;
	sf::Text m_timeText;
	sf::Text m_GameOver;
	sf::Text m_score;
	sf::Text m_restart;
	sf::Text m_highScoreText;
	sf::Text m_highScore;
	sf::Text m_accuracy;
	sf::Text m_accuracyText;
	sf::Text m_close;
	sf::Sound shot;
	int countDown;
	int score;
	int highScore;
	double accuracy;
	double targetHit;
	
	
	

	std::stringstream m_ss;
	std::stringstream m_sScore;
	std::stringstream m_sHighScore;
	std::stringstream m_sAccuracy;
	

};
