#include "physicsObj.h"

physicsObj::physicsObj(GameWindow* gw) : Object(gw) {
	this->gravity = true;
	this->friction = true;
	col.set(42,42);
}

void physicsObj::update(terrain* ter) {
	if(grounded(ter) && vel.y>0) vel.y=0; //Ground collision
	if(leftCol(ter) && vel.x<0) vel.x=0; //Left collision
	if(rightCol(ter) && vel.y>0) vel.x=0; //Right collision


	this->pos.add(vel);
	if(this->friction) vel.mul(FRICTION);
	if(gravity) vel.y += GRAVITY;
}

void physicsObj::accelerate(float x, float y){
	vel.x += x;
	vel.y += y;
}

void physicsObj::setCol(float x, float y) {
	col.set(x,y);
}

bool physicsObj::grounded(terrain* ter) {
	if(ter->getSolid((int)(pos.x+col.x-1), (int)(pos.y+col.y))) return true; //bottom right
	else if(ter->getSolid((int)(pos.x+1), (int)(pos.y+col.y))) return true; //bottom left
	return false;
}

bool physicsObj::leftCol(terrain* ter) {
	if(ter->getSolid((int)(pos.x), (int)(pos.y+col.y-1))) return true; //bottom left
	else if(ter->getSolid((int)(pos.x), (int)(pos.y))) return true; //top left
	return false;
}

bool physicsObj::rightCol(terrain* ter) {
	if(ter->getSolid((int)(pos.x+col.x), (int)(pos.y+col.y-1))) return true; //bottom right
	else if(ter->getSolid((int)(pos.x+col.x), (int)(pos.y))) return true; //top right
	return false;
}

