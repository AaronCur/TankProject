#pragma once
#include <SFML/Graphics.hpp>
#include "KeyHandler.h"

/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>
class Tank
{
public:	
	Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &m_keyHandler);
	void update(double dt);
	void render(sf::RenderWindow & window);
	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void decreaseRotation();
	void decreaseTurretRotation();
	void increaseTurretRotation();
	void snap();
	void fire();
	double m_speed;
	double m_rotation;
	double m_turretRotation;
	double static const DEG_TO_RAD;
	double newPos;
	void handleKeyInput();
	void stop();
	sf::Sprite const & getTurretSprite() const;
	sf::Sprite const & getBaseSprite() const;
	
private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Texture const & m_texture;

	//Bullet m_bullet;
	
	KeyHandler &m_keyHandler;

	
		
};

