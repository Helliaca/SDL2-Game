#include "nav_path.h"

nav_path::nav_path() {
	speed = 1;
	sine_amplitude = 1;
	sine_curveamount = 1;
	active = false;
	agent = NULL;
	mode = LINEAR;
	relPos = 0;
	easeIn = false;
	easeOut = false;
}

nav_path::~nav_path() {
}

void nav_path::init_linear(Vector2 start, Vector2 end, float speed, Object* agent, bool easeIn, bool easeOut) {
	this->agent = agent;
	this->speed = speed;
	this->start = start;
	this->end = end;
	this->mode = LINEAR;
	this->easeIn = easeIn;
	this->easeOut = easeOut;
}

void nav_path::init_bezier(Vector2 start, Vector2 end, Vector2 control, float speed, Object* agent, bool easeIn, bool easeOut) {
	init_linear(start, end, speed, agent, easeIn, easeOut);
	this->bezier_control = control;
	this->mode = BEZIER;
}

void nav_path::init_sine(Vector2 start, Vector2 end, float amp, float curveamount, float speed, Object* agent, bool easeIn, bool easeOut) {
	init_linear(start, end, speed, agent, easeIn, easeOut);
	this->sine_amplitude = amp;
	this->sine_curveamount = curveamount;
	this->mode = SINE;
}

void nav_path::traverse() {
	relPos = 0;
	active = true;
}

void nav_path::update() {
	if(!active) return;
	if(relPos>=1) active=false;

	switch(mode) {
	case LINEAR : {
		agent->setPos(Lerp(start, end, relPos));
		break;
	}
	case SINE : {
		Vector2 target = end;
		target.sub(start);
		target.rotate(90);
		target.normalize();
		target.mul(sine_amplitude*sin(relPos*sine_curveamount*2*PI));
		target.add(Lerp(start, end, relPos));
		agent->setPos(target);
		break;
	}
	case BEZIER : {
		agent->setPos(Bezier(start, bezier_control, end, relPos));
		break;
	}
	}

	float speedMul = 1;
	if(easeIn && relPos<EASE_IN_PERC) speedMul = Lerp(0.01, 1, relPos/EASE_IN_PERC);
	if(easeOut && relPos>1-EASE_OUT_PERC) speedMul = Lerp(1, 0.01, (relPos-(1-EASE_OUT_PERC))/(EASE_OUT_PERC));
	relPos += speed*speedMul;
}

bool nav_path::isBusy() {
	return active;
}
