#include "Bullet.h"
#include "Tank.h"
#include <Thor/Math.hpp>

double const Bullet::DEG_TO_RAD = thor::Pi / 180.0f;

Bullet::Bullet(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &key)
	: m_texture(texture), m_bulletRotation(0), m_speed(1000), m_keyHandler(key)
{

	initSprites(pos);

}

// turret rotation (double), tank position (sf::Vector2f)
void Bullet::shoot(double dt)
{
	fire = true;
	alive = true;
	
	m_bullet.setPosition(m_bullet.getPosition().x + cos(m_tank.m_turretRotation*DEG_TO_RAD) * m_speed * (dt / 1000),
	m_bullet.getPosition().y + sin(m_tank.m_turretRotation* DEG_TO_RAD) * m_speed *(dt / 1000));
}



void Bullet::update(double dt)
{
	/*m_bullet.setPosition = 
	handleKeyInput();
	shoot();*/
	

	/*m_bullet.setPosition(m_bullet.getPosition().x + cos(m_turretRotation*DEG_TO_RAD) * m_speed * (dt / 1000),
	m_bullet.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed *(dt / 1000));*/


	/*m_bullet.setRotation( - 90);*/
	if (fire == true)
	{
		shoot(dt);
		
	}
	
	//m_bullet.setRotation(m_rotation);

}

void Bullet::render(sf::RenderWindow & window)
{
	window.draw(m_bullet);
}


void Bullet::initSprites(sf::Vector2f const & pos)
{
	// Initialise the bullet base
	m_bullet.setTexture(m_texture);
	sf::IntRect bulletRect(8, 178, 8, 8);
	m_bullet.setTextureRect(bulletRect);
	m_bullet.setOrigin(bulletRect.width / 2.0, bulletRect.height / 2.0);
	m_bullet.setPosition(pos);

}



void Bullet::setPos(sf::Vector2f pos)
{
	m_bullet.setPosition(pos);
}

sf::Sprite const & Bullet::getBulletSprite() const
{
	return m_bullet;
}




void Bullet::stop()
{
	m_speed = 0;
}