#include "boss_TailSegment.h"

boss_TailSegment::boss_TailSegment(GameWindow* gw) : AdvImage(gw) {
	angle = 180;
	next = NULL;
	previous = NULL;
	vel.x = vel.y = 0;
	acel.x = acel.y = 0;
	Avel = 0;
	Aacel = 0;
	connector = NULL;
}

boss_TailSegment::~boss_TailSegment() {
	delete next;
}

void boss_TailSegment::buildTail(int num, boss_TailSegment* prev) {
	this->previous = prev;
	if(num>0) {
		connector = new boss_TailSegmentConnector(this->gw);
		connector->loadTexture(BOSS_TAILSEGMENTCONNECTOR_SPRITE);
		this->loadTexture(BOSS_TAILSEGMENT_SPRITE);
		this->setPos(this->intenPos());
		next = new boss_TailSegment(this->gw);
		next->buildTail(num-1, this);
	}
	else if(num==0) {
		this->loadTexture(BOSS_TAILSEGMENT_SPRITE_END);
		this->setPos(this->intenPos());
	}
}

void boss_TailSegment::draw() {
	if(connector!=NULL) connector->draw();
	AdvImage::draw();
	if(next!=NULL) next->draw();
}

void boss_TailSegment::update() {
	if(previous!=NULL) {
		//Get acceleration
		acel.x = intenPos().x - pos.x;
		acel.y = intenPos().y - pos.y;
		Aacel = intenAngle() - angle;
		acel.mul(BOSS_TAILSEGMENT_ACEL_MULTIPLIER);
		Aacel *= BOSS_TAILSEGMENT_AACEL_MULTIPLIER;

		//Add acceleration to velocity
		vel.add(acel);
		Avel += Aacel;
		vel.mul(BOSS_TAILSEGMENT_VEL_MULTIPLIER);
		Avel *= BOSS_TAILSEGMENT_AVEL_MULTIPLIER;

		//Apply velocity/angle
		angle += Avel;
		pos.add(vel);
	}
	AdvImage::update();
	if(next!=NULL) next->update();
	if(connector!=NULL && next!=NULL) connector->update(this->getMidLowerPoint(), next->getMidUpperPoint());
}

Vector2 boss_TailSegment::intenPos() {
	if(previous==NULL) return this->pos;
	Vector2 dirVec; //Direction of rotation of previous segment
	dirVec.fromAngle(previous->angle);
	dirVec.mul(BOSS_TAILSEGMENT_DISTANCE);
	//dirVec.y *= -1.0; //Because all TailSegments are rotated 180° by default
	dirVec.add(previous->pos);
	return dirVec;
}

double boss_TailSegment::intenAngle() {
	Vector2 down;
	down.y=-1;
	down.x=0;
	if(previous==NULL) return this->angle;
	if(vel.length()<BOSS_TAILSEGMENT_BLEND_VELOCITY) return previous->angle;
	double ret = vel.angle(down);
	ret = 180 - ret;
	while(ret<0) ret+=360;
	while(ret>360) ret-=360;
	return ret;
}

Vector2 boss_TailSegment::getMidUpperPoint() {
	Vector2 center = pos;
	center.add(this->texr.w*0.5, this->texr.h*0.5);
	Vector2 ret;
	ret.fromAngle(this->angle);
	ret.mul(-BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_UP);
	ret.add(center);
	return ret;
}

Vector2 boss_TailSegment::getMidLowerPoint() {
	Vector2 center = pos;
	center.add(this->texr.w*0.5, this->texr.h*0.5);
	Vector2 ret;
	ret.fromAngle(this->angle);
	ret.mul(BOSS_TAILSEGMENT_CONNECTOR_HIDE_DISTANCE_DOWN);
	ret.add(center);
	return ret;
}
