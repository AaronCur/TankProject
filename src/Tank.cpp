#include "Tank.h"
#include <Thor/Math.hpp>

double const Tank::DEG_TO_RAD = thor::Pi / 180.0f;

Tank::Tank(sf::Texture const & texture, sf::Vector2f const & pos)
: m_texture(texture),m_rotation(0) , m_speed(0), m_turretRotation(0)
{
	initSprites(pos);
	
}


void Tank::increaseSpeed()
{
	if (m_speed < 100.0)
	{
		m_speed += 0.1;
	}
}

void Tank::decreaseSpeed()
{
	if (m_speed > -100.0)
	{
		m_speed -= 0.1;
	}
}

void Tank::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 360.0)
	{
		m_rotation = 0;
	}
	
}

void Tank::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
	
}

void Tank::decreaseTurretRotation()
{
	m_turretRotation -= 1;
	if (m_turretRotation == 0.0)
	{
		m_turretRotation = 359.0;
	}
}
void Tank::increaseTurretRotation()
{
	m_turretRotation += 1;
	if (m_turretRotation == 360)
	{
		m_turretRotation = 0;
	}
}


void Tank::update(double dt)
{	
	m_tankBase.setPosition(m_tankBase.getPosition().x + cos(m_rotation*DEG_TO_RAD) * m_speed * (dt / 1000),
		m_tankBase.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed *(dt / 1000));
	m_tankBase.setRotation(m_rotation);

	m_turret.setPosition(m_tankBase.getPosition());

	m_turret.setRotation(m_rotation + m_turretRotation);
		
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
}


void Tank::initSprites(sf::Vector2f const & pos)
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_tankBase.setPosition(pos);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	m_turret.setPosition(pos);

}