#ifndef ECOSYSTEM_HPP
#define ECOSYSTEM_HPP

#include "../Soup/Jackstd.hpp"
#include "../Soup/Graphics.hpp"
#include "../Soup/Grid.hpp"

class Blobber {
public:
	Grouper<Blobber*> grouper;
	Gridder blobGridder, mainGridder;
	Iconer  iconOut, iconFill;
	
	Colour col;
	Vec2f pos;
	bool die = false;

	Blobber();
	void setPos(Vec2f p);
	void setCol(Colour c);
};


class Gobbler {
public:
	Grouper<Gobbler*> grouper;
	Iconer icon;
	Gridder gridder;
	Vec2f pos, vel, dir;
	
	float health = 100.;
	
	Gobbler();
	void setPos(Vec2f p);
	void update();
};


class Ecosystem {
public:
	Group<Blobber*> blobbers;
	Group<Gobbler*> gobblers;
	Icon circle, circleBack, star;
	Grid blobGrid, mainGrid;
	
	float hurt = 4.0;
	float eat  = 10.0;
	
	
	Ecosystem();
	Blobber *newBlobber();
	Blobber *spawnBlobber();
	
	Gobbler *newGobbler();
	Gobbler *spawnGobbler();
	
	void update();
	void drawOn(sf::RenderTarget &target);
};

#endif
