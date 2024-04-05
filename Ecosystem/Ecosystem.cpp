#include "Ecosystem.hpp"

Blobber::Blobber() :
grouper(this),
mainGridder(this),
blobGridder(this) {
	iconFill.setRect(Rectf(2.0, 2.0, -1.0, -1.0));
	iconOut.setRect(Rectf(2.2, 2.2, -1.1, -1.1));
	iconOut.setCol(Colour(68, 68, 68));
}

void
Blobber::setPos(Vec2f p) {
	pos = p;
	iconFill.setPos(p);
	iconOut.setPos(p);
	mainGridder.setPos(p);
	blobGridder.setPos(p);
}

void
Blobber::setCol(Colour c) {
	col = c;
	iconFill.setCol(c);
}



Gobbler::Gobbler() :
grouper(this),
gridder(nullptr) {
	icon.setRect(Rectf(3, 3, -1.5, -1.5));
	dir = Vec2f_randNorm();
	vel = dir * 0.4;
}

void
Gobbler::setPos(Vec2f p) {
	pos = p;
	gridder.setPos(p);
	icon.setPos(p);
}

void
Gobbler::update() {
	health -= 1.0;
	
	
	Vec2f prey;
	Blobber *b;
	gridder.resetLocals();
	while (gridder.pollLocals((void**)&b)) {
		if (b == nullptr) continue;
		
		Vec2f vec  = b->pos - pos;
		float len2 = vec.len2();
		if (len2 > 20*20) continue; 
		
		if (len2 < 2*2) {
			health += 6.0;
			if (health > 100.) health = 100.;
			delete b;
			continue;
		}
		
		float invlen2 = 1.0 / len2;
		prey += vec * invlen2;
	}
	prey.normalise();
	
	dir += prey * 0.2;
	dir.normalise();
	vel = dir * 0.4;
}



Ecosystem::Ecosystem() :
blobGrid(Rectf(260, 260), 2 ),
mainGrid(Rectf(260, 260), 20) {
	circleBack.loadFile("Soup/Resources/Blob.png");
	circle.loadFile("Soup/Resources/Blob.png");
	star.loadFile("Soup/Resources/Star.png");
}

Blobber*
Ecosystem::newBlobber() {
	Blobber *b = new Blobber;
	b->grouper.setGroup(blobbers);
	b->mainGridder.setGrid(mainGrid);
	b->blobGridder.setGrid(blobGrid);
	b->iconFill.setIcon(circle);
	b->iconOut.setIcon(circleBack);
	return b;
}

Blobber*
Ecosystem::spawnBlobber() {
	Blobber *b = newBlobber();
	b->setCol(Colour(86, 44, 213));
	b->setPos(Vec2f_rand(blobGrid.rect()));
	return b;
}




Gobbler*
Ecosystem::newGobbler() {
	Gobbler *g = new Gobbler;
	g->grouper.setGroup(gobblers);
	g->gridder.setGrid(mainGrid);
	g->icon.setIcon(star);
	return g;
}

Gobbler*
Ecosystem::spawnGobbler() {
	Gobbler *g = newGobbler();
	g->setPos(Vec2f_rand(mainGrid.rect()));
	return g;
}


void mutateBits(void *arr, size_t size, int odds) {
	for (int i=0; i<size; i++)
		if (diceroll(odds))
			((uint8_t*)arr)[i] ^= 1ul << randint(0, 7);
}


void
Ecosystem::update() {
	for (int i=0; i<blobbers.count; i++) {
		if (diceroll(300)) {
			Blobber *b = blobbers[i];
			Vec2f cpos = b->pos;
			cpos += Vec2f_randNorm() * randflt(1.0, 2.0);
			cpos.clamp(blobGrid.rect());
			
			if (blobGrid.inRange(cpos, 1.0))
				continue;
				
			Blobber *c = newBlobber();
			c->setPos(cpos);
			c->col = b->col;
			mutateBits(&c->col, sizeof(Colour), 100);
			c->setCol(c->col);
		}
	}
	
	
	for (int i=0; i<gobblers.count; i++) {
		Gobbler *g = gobblers[i];
		
		if (g->health < 0.) {
			delete g;
			i--;
			continue;
		}
		
		if (diceroll(2600)) {
			Gobbler *c = newGobbler();
			c->setPos(g->pos);
		}
		
		
		g->update();
		Vec2f pos = g->pos + g->vel;
		pos.clamp(mainGrid.rect());
		g->setPos(pos);
	}
}



void
Ecosystem::drawOn(sf::RenderTarget &target) {
	circleBack.draw(target);
	circle.draw(target);
	star.draw(target);
}
