#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "yaml-cpp\yaml.h"

struct ObstacleData
{
  std::string m_type;
  sf::Vector2f m_position;
  double m_rotation;
};

struct BackgroundData
{
   std::string m_fileName;
};

struct TankData
{
  sf::Vector2f m_position;
  
};
//Set up new struct for the target
struct TargetData
{
	
	sf::Vector2f m_position;
	double m_offset;
};


struct LevelData
{
   BackgroundData m_background;
   TankData m_tank;
   TargetData m_target;
   std::vector<ObstacleData> m_obstacles;
};

class LevelLoader
{
public:

   LevelLoader();

   static bool load(int nr, LevelData& level);
};
