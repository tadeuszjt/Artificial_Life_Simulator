#include "../Soup/Window.hpp"
#include "../Soup/Gui.hpp"
#include "Swarms.hpp"
#include "SwarmsPanel.hpp"
SoupWindow swarmsWindow;
Swarms swarms;
SwarmsPanel panel;



void swarmsMouse(Vec2i pos, bool press, bool release) {
	panel.mouse(pos, press, release);
	swarms.separation = panel.separate.spinBox.value();
	swarms.alignment  = panel.align.spinBox.value();
	swarms.cohesion   = panel.cohere.spinBox.value();
	swarms.speed      = panel.speed.spinBox.value();
}


bool swarmsPause = false;
void swarmsKeyboard(sf::Keyboard::Key key, bool press, bool release) {
	if (press) { 
		switch (key) {
			case sf::Keyboard::Space :
				swarmsPause = !swarmsPause;
				break;
		}
	}
}

void swarmsDraw(sf::RenderTarget &target) {
	if (!swarmsPause) swarms.update();
	swarms.draw(target);
}

void swarmsDrawGui(sf::RenderTarget &target) {
	panel.drawOn(target);
}



int runSwarms() {
	for (int i=0; i<2000; i++)
		swarms.newSwarmer();
	
	swarmsWindow.setDrawCB(swarmsDraw);
	swarmsWindow.setDrawGuiCB(swarmsDrawGui);
	swarmsWindow.setMouseCB(swarmsMouse);
	swarmsWindow.setKeyboardCB(swarmsKeyboard);
	swarmsWindow.run();
	return 0;
}
