#include "Target.h"
#include <Thor/Math.hpp>
/// <summary>
/// @author Aaron Curry
/// @date 0/12/2016
/// @id C00202505
/// @version 1.0
/// @timeTaken approximately 31 hours
/// </summary>

double const Target::DEG_TO_RAD = thor::Pi / 180.0f;

Target::Target(sf::Texture const & texture, sf::Vector2f const & position, KeyHandler &key)
	: m_texture2(texture),m_keyHandler(key), hit(false)
{
	alive = true;
	srand(time(NULL));
	
	
	double offset = 20;

	initTargetSprite(position, offset);
	

}




void Target::update(double dt)
{
	/*handleKeyInput();

	m_tankBase.setPosition(m_tankBase.getPosition().x + cos(m_rotation*DEG_TO_RAD) * m_speed * (dt / 1000),
		m_tankBase.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed *(dt / 1000));
	m_tankBase.setRotation(m_rotation);

	m_turret.setPosition(m_tankBase.getPosition());

	m_turret.setRotation(m_rotation + m_turretRotation);*/

}

void Target::render(sf::RenderWindow & window)
{
	window.draw(m_target);
	
}


void Target::initTargetSprite(sf::Vector2f const & position, double offset)
{
	alive = true;
	m_target.setTexture(m_texture2);
	double offSetX = rand() % static_cast<int>(offset);
	double offSetY = rand() % static_cast<int>(offset);
	m_target.setPosition(position.x + offset,position.y + offset);
	
	


}


//void Tank::fire(double dt)
//{
//	m_bullet.setPosition(m_tankBase.getPosition().x + cos(m_rotation*DEG_TO_RAD) * m_speed * (dt / 1000),
//    m_tankBase.getPosition().y + sin(m_rotation * DEG_TO_RAD) * m_speed *(dt / 1000));
//	m_tankBase.setRotation(m_rotation);
//}
sf::Sprite const & Target::getTargetSprite() const
{
	return m_target;
}



