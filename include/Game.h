#pragma once

#include <SFML/Graphics.hpp>
#include "LevelLoader.h"
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
	bool checkTankWallCollision();
	
	// main window
	sf::RenderWindow m_window;
	sf::Sprite m_sprite;
	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;
	sf::Texture m_texture;
	std::vector<sf::Sprite>  m_sprites;
	std::unique_ptr<Tank> m_tank;
	std::string timerValue;
	// A container for the Wall sprites
	std::vector<std::unique_ptr<sf::Sprite>> m_wallSprites;
	KeyHandler m_keyHandler;
	sf::Clock m_clock;
	double m_timeSinceLastUpdate;
	sf::Font m_font;
	sf::Text m_text;
	int countDown;

	std::stringstream m_ss;
	

};
