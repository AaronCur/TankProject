#pragma once
#include <SFML/Graphics.hpp>
#include "KeyHandler.h"
#include "SFML/Audio.hpp"
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
	void checkBoundary();
	double m_speed;
	double m_rotation;
	double m_turretRotation;
	double m_bulletRotation;
	double m_bulletRotationPos;
	int m_bulletSpeed;
	double shots;
	bool bulletAlive;
	bool fire;
	double static const DEG_TO_RAD;
	double newPos;
	void handleKeyInput(double dt);
	void stop();
	void shoot(double dt);
	
	sf::Sprite const & getTurretSprite() const;
	sf::Sprite const & getBaseSprite() const;
	sf::Sprite const & getBulletSprite() const;

	
	
private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Sprite m_bullet;
	sf::Texture const & m_texture;
	sf::SoundBuffer buffer;
	sf::Sound shot;

	
	KeyHandler &m_keyHandler;

	
		
};

