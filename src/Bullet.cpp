#include "Bullet.h"
#include <Thor/Math.hpp>

double const Bullet::DEG_TO_RAD = thor::Pi / 180.0f;

Bullet::Bullet(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &key, Tank m_tank)
	: m_texture(texture), m_rotation(0), m_speed(0), m_turretRotation(0), m_keyHandler(key), alive(false), m_tank(m_tank)
{
	initSprites(pos);
	
	alive = false;
}


//void Tank::increaseTurretRotation()
//{
//	m_turretRotation += 1;
//	if (m_turretRotation == 360)
//	{
//		m_turretRotation = 0;
//	}
//}
//
//void Tank::snap()
//{
//	m_turretRotation = 0;
//}
void Bullet::shoot(std::unique_ptr<Bullet>)
{
	
	/*m_bullet.setPosition(m_tank.)

	m_bullet.setPosition(m_tank.getTurretSprite() + cos(m_rotation*DEG_TO_RAD) * m_speed * (dt / 1000),
	m_tankBase.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed *(dt / 1000));
	m_tankBase.setRotation(m_rotation);

	m_turret.setPosition(m_tankBase.getPosition());

	m_turret.setRotation(m_rotation + m_turretRotation);*/
}

void Bullet::update(double dt)
{
	handleKeyInput();
	
	if (alive == true)
	{
		m_bullet.setPosition(m_tank.getTurretSprite().getPosition().x + cos(m_rotation*DEG_TO_RAD) * m_speed * (dt / 1000),
			m_tank.getTurretSprite().getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed *(dt / 1000));
		m_bullet.setRotation(m_rotation);

		m_bullet.setPosition(m_tank.getTurretSprite().getPosition() );

		m_bullet.setRotation(m_rotation + m_turretRotation);
	}
	

}

void Bullet::render(sf::RenderWindow & window)
{

	window.draw(m_bullet);
}


void Bullet::initSprites(sf::Vector2f const & pos)
{
	// Initialise the tank base
	m_bullet.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_bullet.setTextureRect(baseRect);
	m_bullet.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_bullet.setPosition(pos);
	



}

void Bullet::handleKeyInput()
{

	if (m_keyHandler.isPressed(sf::Keyboard::Key::Space))
	{
		
	}


}

sf::Sprite const & Bullet::getBulletSprite() const
{
	return m_bullet;
}




void Bullet::stop()
{
	m_speed = 0;
}