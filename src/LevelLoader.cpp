#include "LevelLoader.h"
#include <Tank.h>

void operator >> (const YAML::Node& obstacleNode, ObstacleData& obstacle)
{
   obstacle.m_type = obstacleNode["type"].as<std::string>();
   obstacle.m_position.x = obstacleNode["position"]["x"].as<float>();
   obstacle.m_position.y = obstacleNode["position"]["y"].as<float>();
   obstacle.m_rotation = obstacleNode["rotation"].as<double>();
}

void operator >> (const YAML::Node& backgroundNode, BackgroundData& background)
{
   background.m_fileName = backgroundNode["file"].as<std::string>();
}
//Picks one of the 4 corners in the yaml file when spawning tank
void operator >> (const YAML::Node& tankNode, TankData& tank)
{
	srand(time(NULL));
	int rnd = rand() % 4 + 1;
	tank.m_position.x = tankNode["position" + std::to_string(rnd)]["x"].as<float>();
	tank.m_position.y = tankNode["position" + std::to_string(rnd)]["y"].as<float>();
}
//Picks one of the positions in yaml file when spawning the target with a random offset
void operator >> (const YAML::Node& targetNode, TargetData& target)
{
	srand(time(NULL));
	int rnd = rand() % 7 + 1;
	target.m_offset = targetNode["position" + std::to_string(rnd)]["randomOffset"].as<double>();
	int rndOffset = rand() % static_cast<int>(target.m_offset) + 1;

	target.m_position.x = targetNode["position" + std::to_string(rnd)]["x"].as<float>();
	target.m_position.y = targetNode["position" + std::to_string(rnd)]["y"].as<float>();
	
	target.m_position.x += rndOffset;
	target.m_position.y += rndOffset;
}


void operator >> (const YAML::Node& levelNode, LevelData& level)
{
   levelNode["background"] >> level.m_background;

   levelNode["tank"] >> level.m_tank;

   levelNode["target"] >> level.m_target;

   const YAML::Node& obstaclesNode = levelNode["obstacles"].as<YAML::Node>();
   for (unsigned i = 0; i < obstaclesNode.size(); ++i)
   {
	  ObstacleData obstacle;
	  obstaclesNode[i] >> obstacle;
	  level.m_obstacles.push_back(obstacle);
   }
}

LevelLoader::LevelLoader()
{

}

bool LevelLoader::load(int nr, LevelData& level)
{
   std::stringstream ss;
   ss << "./resources/level/level";
   ss << nr;
   ss << ".yaml";

   try
   {
	  YAML::Node baseNode = YAML::LoadFile(ss.str());
	  if (baseNode.IsNull())
	  {
		  std::string message("file: " + ss.str() + " not found");
		  throw std::exception(message.c_str());
	  }
	  baseNode >> level;
   }
   catch(YAML::ParserException& e)
   {
       std::cout << e.what() << "\n";
       return false;
   }
   catch (std::exception& e)
   {
	   std::cout << e.what() << "\n";
	   return false;
   }

   return true;
}
