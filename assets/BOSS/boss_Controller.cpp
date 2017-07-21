#include "boss_Controller.h"

boss_Controller::boss_Controller(GameWindow* gw, terrain* ter) : Object(gw) {
	bossNavigator = new nav_graph(this);
	this->ter = ter;
	tailOffset.set(-100, 30);
	laserOffset.set(120, 160);
	this->head = new boss_Head(gw);
	this->tail = new boss_TailSegment(gw);
	this->tail->buildTail(6, NULL);
	tailWiggleTimer.start();
	laser = new AdvImage(gw);
	laser->loadTexture(LASER_SPRITE);
	laser->center = new SDL_Point();
	laser_impact = new animation(gw);
	laser_impact2 = new animation(gw);
	laser_impact->setAnim(LASER_IMPACT_SPRITE, 1, 4, 100.0f, 1);
	laser_impact->loop = true;
	laser_impact2->setAnim(LASER_IMPACT_SPRITE, 1, 4, 90.0f, 1);
	laser_impact2->loop = true;
	laser_flare = new AdvImage(gw);
	laser_flare->loadTexture(LASER_IMPACT_SPRITE);
	idleAngle = 0;
	laserOn = false;
	tailWiggleAmplitude = 1; //These values aremultiplied with base values from defs.h
	tailWiggleSpeed = 1;
}

boss_Controller::~boss_Controller() {
}

void boss_Controller::update() {
	this->head->setPos(pos);
	this->head->update();

	updateTail(); //update head before this

	if(laserOn) updateLaser();

	bossNavigator->update();
}

void boss_Controller::draw() {
	this->tail->draw();
	this->head->draw();
	if(laserOn) {
		this->laser->draw();
		laser_flare->draw();
	}
}

void boss_Controller::updateLaser() {
	this->laser->setPos(pos.x+laserOffset.x, pos.y+laserOffset.y);
	this->laser->angle = this->head->angle + 90;
	Vector2 lookat;
	lookat.fromAngle(laser->angle);
	Vector2 hit = ter->raycast(laser->getPos(), lookat, 0.1f);
	laser_flare->setPosCenter(hit);
	laser_flare->update();
	laser_impact->setPos(hit.x-laser_impact->getRect().w/2, hit.y-laser_impact->getRect().h+20);
	laser_impact2->setPos(hit.x-laser_impact->getRect().w/2, hit.y-laser_impact->getRect().h+20);
	this->laser->setFromTo(laser->getPos(), hit, true);
	this->laser->update();
	this->laser_impact->update();
	this->laser_impact2->update();
	this->laser_flare->angle += 50;
}

void boss_Controller::updateTail() {
	this->tail->angle = BOSS_DEFAULT_TAIL_ROTATION + tailWiggleAmplitude*BOSS_TAILWIGGLE_AMPLITUDE * sin(tailWiggleTimer.elapsedTime()*BOSS_TAILWIGGLE_SPEED*tailWiggleSpeed);
	Vector2 headCenter;
	headCenter.x = head->getPos().x + head->getRect().w/2;
	headCenter.y = head->getPos().y + head->getRect().h/2;
	Vector2 tmp_tailPos = tailOffset;
	tmp_tailPos.rotate(head->angle);
	tmp_tailPos.add(headCenter);
	this->tail->setPos(tmp_tailPos);
	this->tail->update();
}

void boss_Controller::setTailWiggle(float Amp, float Speed) {
	tailWiggleAmplitude = Amp;
	tailWiggleSpeed = Speed;
}
