#include "animation.h"

void animation::setAnim(const char* path ,int rows, int columns, float deltaT, int direction) {
	this->loadTexture(path);
	this->dir = direction;
	this->rows = rows;
	this->cols = columns;
	this->deltaT = deltaT;
	this->maxFrame = rows*columns;
	if(deltaT<=0) this->manualOverride = true;

	this->texr.w = this->texr.w/cols;
	this->texr.h = this->texr.h/rows;
	this->srcRect.w = this->texr.w;
	this->srcRect.h = this->texr.h;
	setFrame(0);
	innerTimer->start();
}

animation::animation(GameWindow* gw) : Image(gw) {
	manualOverride = dead = loop = false;
	dieOnEnd = true;
	innerTimer = new Timer();
	cols = rows = dir = maxFrame = currFrame = 0;
	deltaT = 0;
}

animation::~animation() {
	delete tex;
	delete innerTimer;
}

void animation::setFrame(int frameNum) {
	if(this->dir==0) { //from bottom right to top left (right to left)
		this->setFrame(maxFrame - (frameNum % maxFrame)); //this wont work...
	}
	if(this->dir==1) { //from top left to bottom right (left to right)
		this->srcRect.y = ((frameNum / cols) % rows) * this->texr.h;
		this->srcRect.x = (frameNum % cols) * this->texr.w;
	}
}

void animation::update() {
	if(dead) return;
	Image::update();
	if(manualOverride) return;
	if(innerTimer->elapsedTime()>deltaT) {
		if(currFrame == maxFrame-1 && dieOnEnd && !dead) {
			dead = true;
			return;
		}
		currFrame = (currFrame + 1) % maxFrame;
		innerTimer->start();
	}
	setFrame(currFrame);
}

void animation::setPos(float x, float y) {
	this->pos.x = x;
	this->pos.y = y;
}

void animation::draw() {
	if(dead) return;
	gw->draw(this->tex, &srcRect, &texr);
}

void animation::reset() {
	dead = false;
	innerTimer->start();
	currFrame = 0;
	setFrame(0);
}
