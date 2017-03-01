#pragma once
#include "entityx/Entity.h"
#include "systems/Events.h"
#include "components/Turret.h"
#include "components/Parent.h"
#include "components/Position.h"
#include "components/Motion.h"
#include "components/Path.h"
#include "utils/BTMath.h"
#include <SFML/Graphics.hpp>
#include <Thor/Vectors.hpp>
#include <iostream>
#include <queue>

class TankAi 
{
public:

   TankAi(std::vector<sf::CircleShape> const & obstacles, std::vector<sf::CircleShape> const &path, entityx::Entity::Id id);


   void update(entityx::Entity::Id playerId,  
	           entityx::Entity::Id aiId,
               entityx::EntityManager& entities,
               double dt);
 
   enum class AiType
   {
	   AI_ID_NONE, 
	   AI_ID_SEEK_SHOOT_AT_PLAYER
   };
   
private:
	sf::Vector2f seek(entityx::Entity::Id playerId,
					  entityx::Entity::Id aiId,
					  entityx::EntityManager& entities) const;

	sf::Vector2f pathFollowing(entityx::Entity::Id pathId,
		entityx::Entity::Id aiId,
		entityx::EntityManager& entities) ;

	sf::Vector2f collisionAvoidance(entityx::Entity::Id aiId, 
						            entityx::EntityManager& entities);

	const sf::CircleShape findMostThreateningObstacle(entityx::Entity::Id aiId,
													  entityx::EntityManager& entities) ;

	int currentNode = 0;
	

	sf::Vector2f m_velocity;

	sf::Vector2f m_steering;

	sf::Vector2f m_ahead;

	sf::Vector2f m_halfAhead;

	

	const float MAX_SEE_AHEAD = 50.0f;

	const float MAX_AVOID_FORCE = 50.0f;

	const float MAX_FORCE = 10.0f;

	float MAX_SPEED = 50.0f;


	std::vector<sf::CircleShape> const & m_obstacles;

	std::vector<sf::CircleShape> const & m_path;

	enum class AiBehaviour
	{
		SEEK_PLAYER,
		PATH_FOLLOWING,
		STOP,
		RETREAT
	} m_aiBehaviour;
  

};

