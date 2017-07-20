#include "background.h"

background::background(GameWindow* gw) : Image(gw) {
	moveDistance.x = -BGWIDTH + SWIDTH; //These should be negative numbers, as the background scrolls to the left
	moveDistance.y = -BGHEIGHT + SHEIGHT;
}

background::~background() {}

void background::update(Vector2 ViewPortPos) {
	this->pos.x = Lerp(0, moveDistance.x, ViewPortPos.x/(LEVELWIDTH-SWIDTH));
	this->pos.y = Lerp(0, moveDistance.y, ViewPortPos.y/(LEVELHEIGHT-SHEIGHT));
	Image::update();
}

void background::draw() {
	gw->drawOverride(this->tex, NULL, &texr);
}
