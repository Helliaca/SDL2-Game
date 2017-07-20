#include "missile.h"

missile::missile(GameWindow* gw) : AdvImage(gw) {
	loadTexture(MISSILESPRITE);
	dead = false;
	terrainCollision = false;
	lifetime = 15000; //15 seconds
	lifeTimer.start();
	trail = new animation(gw);
	trail->setAnim(FIRESPRITE, 5, 5, 0.3f, 1);
	trail->dieOnEnd = false;
	trail->loop = true;
	randomDrift.set(0.3*getRandDecimal(), 0.3*getRandDecimal());
	randomDriftOffset = getRandInteger(0, 50000);
	randomDriftSpeed = getRandInteger(300, 800);
	flameTrail = true;
	straight = false;
	explosion = new animation(gw);
	explosion->setAnim(LARGEEXPLOSIONSPRITE, 4, 4, 25, 1);
	explosion->loop = false;
	explosion->dieOnEnd = true;
	hitMarker = new Image(gw);
	markHit = true;
	hitMarker->loadTexture(HITMARKER);
}

missile::missile(GameWindow* gw, int spawnX, int spawnY, float velX, float velY, bool drop) : AdvImage(gw) {
	if(drop) {
		terrainCollision = true;
		flameTrail = false;
		straight = true;
		loadTexture(MISSILEDROPSPRITE);
		hitMarker = new Image(gw);
		markHit = true;
		hitMarker->loadTexture(HITMARKER);
	}
	else {
		markHit = false;
		terrainCollision = false;
		flameTrail = true;
		straight = false;
		trail = new animation(gw);
		trail->setAnim(FIRESPRITE, 5, 5, 0.2f, 1);
		trail->dieOnEnd = false;
		trail->loop = true;
		randomDrift.set(0.3*getRandDecimal(), 0.3*getRandDecimal());
		randomDriftOffset = getRandInteger(0, 50000);
		randomDriftSpeed = getRandInteger(100, 1000);
		loadTexture(MISSILESPRITE);
	}
	vel.x = velX;
	vel.y = velY;
	pos.x = spawnX;
	pos.y = spawnY;
	dead = false;
	lifetime = 15000; //15 seconds
	lifeTimer.start();
	explosion = new animation(gw);
	explosion->setAnim(LARGEEXPLOSIONSPRITE, 4, 4, 25, 1);
	explosion->loop = false;
	explosion->dieOnEnd = true;
}

missile::~missile() {
}

void missile::update(terrain* ter) {
	if(lifeTimer.elapsedTime()>lifetime) dead=true;
	if(!dead && terrainCollision && ter->getSolid(pos.x, pos.y)) {
		explosion->setPos(pos.x, pos.y-75);
		explosion->reset();
		dead = true;
	}
	if(dead && terrainCollision) {
		explosion->update();
		return;
	}

	if(!straight) vel.y = randomDrift.y * sin(randomDriftOffset + lifeTimer.elapsedTime()/randomDriftSpeed);
	Vector2 def;
	def.set(1,0);
	this->angle = vel.angle(def);

	if(flameTrail) {
		trail->setPos(pos.x-60, pos.y-60);
		trail->update();
	}

	if(markHit) {
		setHitMarker(ter);
		hitMarker->update();
	}

	this->pos.add(vel);
	AdvImage::update();
}

void missile::setPos(Vector2 pos) {
	this->pos = pos;
}

Vector2 missile::getPos() {
	return this->pos;
}

void missile::launch(Vector2 vel) {
	this->vel = vel;
}

void missile::draw() {
	if(dead && terrainCollision) {
		explosion->draw();
		return;
	}
	if(flameTrail) trail->draw();
	if(markHit) hitMarker->draw();
	AdvImage::draw();
}

void missile::reset() {
	lifeTimer.start();
	dead = false;
}

void missile::setHitMarker(terrain* ter) {
	Vector2 markerPos = ter->raycast(pos, vel, 3.0f);
	markerPos.y -= hitMarker->getRect().h;
	hitMarker->setPos(markerPos);
}
