#include "utils/CollisionBox.h"

CollisionBox::CollisionBox()
{
}

CollisionBox::CollisionBox(int w, int h)
: m_w(w)
, m_h(h)
, m_offset()
, m_objectPosition()
{
}

CollisionBox::CollisionBox(int w, int h, const sf::Vector2f& offset)
: m_w(w)
, m_h(h)
, m_offset(offset)
, m_objectPosition()
{
}

void CollisionBox::setObjectPosition(const sf::Vector2f& objectPosition)
{
   m_objectPosition = objectPosition;
}

sf::IntRect CollisionBox::getRect() const
{
   sf::IntRect rect;
   rect.width = m_w;
   rect.height = m_h;
   rect.left = static_cast<int>(m_objectPosition.x);
   rect.top = static_cast<int>(m_objectPosition.y);
   return rect;
}

bool CollisionBox::checkCollision(const CollisionBox& box)
{	
    sf::IntRect thisRect(getRect());
	
    sf::IntRect thatRect(box.getRect());
	
    return thisRect.intersects(thatRect);
}
