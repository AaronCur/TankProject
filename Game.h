#pragma once

#include <SFML/Graphics.hpp>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// @author AC
/// This will be a single class framework for learning about SFML.
/// </summary>
class Game
{
public:
	Game();	
	void run();
protected:	
	void update(double dt);
	void render();
	void processEvents();	
	void processGameEvents(sf::Event&);
	
	// main window
	sf::RenderWindow m_window;
	
};
