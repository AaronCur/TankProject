
#pragma once
#include <SFML/Graphics.hpp>
#include "KeyHandler.h"

// <summary>
/// @brief A simple Target controller.
/// 
/// This class will manage all target attributes.
/// </summary>
class Target
{
public:
	Target(sf::Texture const & texture, sf::Vector2f const & position, KeyHandler &m_keyHandler);
	void update(double dt);
	void render(sf::RenderWindow & window);

	double static const DEG_TO_RAD;
	double newPos;
	void handleKeyInput();
	void spawn();
	void stop();
	bool alive;
	bool hit;
	sf::Sprite const & getTargetSprite() const;
	

private:
	void initTargetSprite(sf::Vector2f const & position, double offset);
	sf::Sprite m_target;
	sf::Texture const & m_texture2;
	KeyHandler &m_keyHandler;



};

