#include "boss_TailSegmentConnector.h"

boss_TailSegmentConnector::boss_TailSegmentConnector(GameWindow* gw) : AdvImage(gw) {
	this->center = new SDL_Point();
	center->x = 0;
	center->y = 0;
}

boss_TailSegmentConnector::~boss_TailSegmentConnector() {
}

void boss_TailSegmentConnector::update(Vector2 from, Vector2 to) {
	this->setFromTo(from, to, true);
	AdvImage::update();
}
