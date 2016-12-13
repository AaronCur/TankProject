#include "Tank.h"
#include <Thor/Math.hpp>


double const Tank::DEG_TO_RAD = thor::Pi / 180.0f;

Tank::Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler &key)
	: m_texture(texture),m_rotation(0) , m_speed(0), m_bulletRotation(0),m_bulletRotationPos(0), m_bulletSpeed(700), m_turretRotation(0), m_keyHandler(key), fire(false), bulletAlive(false)
	,shots(0)
	
{
	initSprites(pos);
	//Load in sound file for the tank firing
	buffer.loadFromFile("./resources/TankFire.wav");
	shot.setBuffer(buffer);
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
//Resets the turret positon to be in line with the tank when c is presse
void Tank::snap()
{
	m_turretRotation = 0;
}


void Tank::update(double dt)
{	
	handleKeyInput(dt);
	
	m_tankBase.setPosition(m_tankBase.getPosition().x + cos(m_rotation*DEG_TO_RAD) * m_speed * (dt / 1000),
	                       m_tankBase.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed *(dt / 1000));
	m_tankBase.setRotation(m_rotation);

	m_turret.setPosition(m_tankBase.getPosition());

	m_turret.setRotation(m_rotation + m_turretRotation);

	
	
	checkBoundary();
	
	//Bullet movement update
	if (bulletAlive == true)
	{
		m_bullet.setPosition(m_bullet.getPosition().x + cos(m_bulletRotation*DEG_TO_RAD) * m_bulletSpeed * (dt / 1000),
			m_bullet.getPosition().y + sin(m_bulletRotation * DEG_TO_RAD) * m_bulletSpeed *(dt / 1000));
		
	}
	
	

	
	
		
}
//Draws the tank base and turret but Only draws the bullet when its alive

void Tank::render(sf::RenderWindow & window) 
{
	if (bulletAlive == true)
	{
		window.draw(m_bullet);
	}

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

	// Initialise the bullet
	m_bullet.setTexture(m_texture);
	sf::IntRect bulletRect(8, 178, 8, 8);
	m_bullet.setTextureRect(bulletRect);
	m_bullet.setOrigin(bulletRect.width / 3.0, bulletRect.height / 2.0);
	m_bullet.setPosition(pos);
	
}
//This method is only called when the bullet is initially fired setting its
//Position and direction
void Tank::shoot(double dt)
{
	
		m_bulletRotation = m_rotation + m_turretRotation;


		m_bullet.setRotation(m_bulletRotation - 90);
		m_bullet.setPosition(m_turret.getPosition());
		m_bulletRotation = m_rotation + m_turretRotation;
		m_bulletRotationPos = m_turretRotation - 90;

		//Sound file is played
		shot.play();

		shots++; 
	
	
		
		
	
}
//Collision with bullet and window and tank with window
void Tank::checkBoundary()
{
	if (!(m_bullet.getPosition().x > 0  && m_bullet.getPosition().x < 1440
		&& m_bullet.getPosition().y > 0 && m_bullet.getPosition().y < 900))
	{
		
		
		bulletAlive = false;
		
	}

	if (!(m_tankBase.getPosition().x > 20 && m_tankBase.getPosition().x < 1420
		&& m_tankBase.getPosition().y > 20 && m_tankBase.getPosition().y < 890))
	{

		m_speed = 15;
	}

	
}
//To detect any key presses and call the appropriate move / shoot methods
void Tank::handleKeyInput(double dt)
{
	if (m_keyHandler.isPressed(sf::Keyboard::Key::Up))
	{
		increaseSpeed();

	}
	if (m_keyHandler.isPressed(sf::Keyboard::Key::Down))
	{
		decreaseSpeed();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Key::Left))
	{
		decreaseRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Key::Right))
	{
		increaseRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Key::Z))
	{
		decreaseTurretRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Key::X))
	{
		increaseTurretRotation();
	}
	//Resets the turret positon to be in line with the tank when c is pressed

	if (m_keyHandler.isPressed(sf::Keyboard::Key::C))
	{
		snap();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Key::Space))
	{
		//Bullet has to die before you can fire again
		//By hitting the window boundaries / target/ wall.
		if (bulletAlive == false)
		{
			bulletAlive = true;
			
			shoot(dt);
			
		}
			
		
	}


}

//Gets the tank and bullet sprites for use with collision detection
sf::Sprite const & Tank::getTurretSprite() const
{
	return m_turret;
}

sf::Sprite const & Tank::getBaseSprite() const
{
	return m_tankBase;
}
sf::Sprite const & Tank::getBulletSprite() const
{
	return m_bullet;
}

//When tank hits the wall, tank slows down and goes backwards
void Tank::stop()
{
	if (m_speed > 0)
	{
		m_speed -= 7;
		//m_speed = 0;
	}
	
}