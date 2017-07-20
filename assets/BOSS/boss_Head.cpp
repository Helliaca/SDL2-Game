#include "boss_Head.h"

boss_Head::boss_Head(GameWindow* gw) : AdvImage(gw) {
	this->loadTexture(BOSS_HEAD_SPRITE);
	idleAngle = 0;
	idleOffsetMul.set(1,1);
	alt = new AdvImage(gw);
	alt->loadTexture(BOSS_HEAD_SPRITE_ALTERNATIVE);
	laser = false;
}

boss_Head::~boss_Head() {
}

void boss_Head::update() {
	Vector2 headPos = pos;
	idleAngle += BOSS_IDLEANIMATION_SPEED;
	idleOffset.fromAngle(idleAngle);
	idleOffset.mul(BOSS_IDLEANIMATION_RADIUS);
	idleOffset.x *= idleOffsetMul.x;
	idleOffset.y *= idleOffsetMul.y;
	headPos.add(idleOffset);
	this->setPos(headPos);

	alt->angle = this->angle;
	alt->setPos(pos);
	alt->update();

	AdvImage::update();
}

void boss_Head::tilt(double angle) {
	this->angle += angle;
}

void boss_Head::setTilt(double angle) {
	this->angle = angle;
}

void boss_Head::setIdleOffsetMul(float x, float y) {
	idleOffsetMul.set(x,y);
}

void boss_Head::draw() {
	if(laser) alt->draw();
	else AdvImage::draw();
}
