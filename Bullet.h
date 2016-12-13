#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "KeyHandler.h"
#include "Tank.h"

/// <summary>
/// @brief A simple bullet controller.
/// 
/// This class will manage all bullet movement and rotations.
/// </summary>
class Tank

class Bullet
{
public:
	Bullet(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &m_keyHandler);
	void update(double dt);
	void render(sf::RenderWindow & window);
	double m_speed;
	double m_bulletRotation;
	double static const DEG_TO_RAD;
	double newPos;
	bool fire;
	bool alive;
	void handleKeyInput();
	void stop();
	void shoot(double dt);
	void setPos(sf::Vector2f pos);
	sf::Sprite const & getBulletSprite() const;
	//std::unique_ptr<Tank> m_tank;


private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_bullet;
	sf::Texture const & m_texture;
	Tank *m_tank;

	KeyHandler &m_keyHandler;



};

