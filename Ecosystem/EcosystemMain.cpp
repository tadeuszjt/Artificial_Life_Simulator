#include "EcosystemMain.hpp"
SoupWindow ecosystemWindow;
Ecosystem  eco;


void ecosystemMouse(Vec2i pos, bool press, bool release) {
}


bool pause = false;
int ecosystemStep = 1;
void ecosystemKeyboard(sf::Keyboard::Key key, bool press, bool release) {
	if (press) {
		switch (key) {
			case sf::Keyboard::Space : {
				pause = !pause;
			} break;
			
			case sf::Keyboard::Add : {
				ecosystemStep *= 2;
			} break;
			
			case sf::Keyboard::Subtract : {
				ecosystemStep /= 2;
				if (ecosystemStep < 1) ecosystemStep = 1;
			} break;
			
		}
	}
}

void ecosystemDraw(sf::RenderTarget &target) {
	if (!pause) {
		for (int i=0; i<ecosystemStep; i++)
			eco.update();
	}
	eco.drawOn(target);
}

void ecosystemDrawGui(sf::RenderTarget &target) {
}



int runEcosystem() {
	for (int i=0; i<10000; i++)
		eco.spawnBlobber();
	
	for (int i=0; i<10; i++)
		eco.spawnGobbler();
	
	
	ecosystemWindow.setDrawCB(ecosystemDraw);
	ecosystemWindow.setDrawGuiCB(ecosystemDrawGui);
	ecosystemWindow.setMouseCB(ecosystemMouse);
	ecosystemWindow.setKeyboardCB(ecosystemKeyboard);
	ecosystemWindow.run();
	return 0;
}
