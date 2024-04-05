#ifndef SWARMS_HPP
#define SWARMS_HPP

#include "../Soup/Grid.hpp"
#include "../Soup/Graphics.hpp"
#include "../Soup/Jackstd.hpp"

class Swarmer {
public:
	float speed      = 0.0;
	float alignment  = 0.0;
	float cohesion   = 0.0;
	float separation = 0.0;

	Iconer iconOut, iconBack;
	Gridder gridder;
	Vec2f pos, vel, dir;
	Vec2f wall;
	
	
	Swarmer();
	void setPos(Vec2f p);
	void update();
};

class Swarms {
public:
	Dtab<Swarmer*> swarmers;
	Icon shipOut, shipBack;
	Grid grid;
	
	float speed      = 0.0;
	float alignment  = 0.0;
	float cohesion   = 0.0;
	float separation = 0.0;
	
	Swarmer *newSwarmer();
	Swarms();
	Vec2f wall(Vec2f pos);
	void update();
	void draw(sf::RenderTarget &target); 

};

#endif
