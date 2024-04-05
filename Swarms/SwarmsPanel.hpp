#ifndef SWARMSPANEL_HPP
#define SWARMSPANEL_HPP

#include "../Soup/Gui.hpp"

class SwarmsControl {
public:
	GuiText label;
	GuiSpinbox spinBox;
	
	void setRect(Recti r) {
		spinBox.setRect(Recti(78, r.h, r.xopp()-78, r.y));
		Recti trec = spinBox.text.rect();
		label.setRect(Recti(r.w, trec.h, r.x, trec.y));
	}
	
	void mouse(Vec2i pos, bool press, bool release) {
		spinBox.mouse(pos, press, release);
	}
	
	void drawOn(sf::RenderTarget &target) const {
		label.drawOn(target);
		spinBox.drawOn(target);
	}
};


class SwarmsPanel {
public:
	GuiWindow  window;
	SwarmsControl speed, align, cohere, separate;
	
	SwarmsPanel() {
		speed.label.printf("Speed:");
		align.label.printf("Alignment:");
		cohere.label.printf("Cohesion:");
		separate.label.printf("Separation:");
		
		setRect(Recti(200, 220));
		window.title.printf("Swarms");
	}
	
	void mouse(Vec2i pos, bool press, bool release) {
		speed.mouse(pos, press, release);	
		align.mouse(pos, press, release);	
		cohere.mouse(pos, press, release);	
		separate.mouse(pos, press, release);	
		
		Recti prev = window.rect();
		window.mouse(pos, press, release);
		Recti wrec = window.rect();
		if (wrec.w <= 200) wrec.w = 200;
		if (wrec.h <= 220) wrec.h = 220;
		if (wrec != prev)  setRect(wrec);
	}
	
	void drawOn(sf::RenderTarget &target, sf::RenderStates states=sf::RenderStates::Default) const {
		window.drawOn(target, states);
		speed.drawOn(target);
		align.drawOn(target);
		cohere.drawOn(target);
		separate.drawOn(target);
	}
	
	void setRect(Recti r) {
		window.setRect(r);
		Recti cen = window.margin.rect(1, 1);
		
		speed.setRect(Recti(cen.w, 24, cen.x, cen.y + 20));
		align.setRect(Recti(cen.w, 24, cen.x, cen.y + 60));
		cohere.setRect(Recti(cen.w, 24, cen.x, cen.y + 100));
		separate.setRect(Recti(cen.w, 24, cen.x, cen.y + 140));
	}
	
	Recti rect() const {
		return window.rect();
	}
};


#endif
