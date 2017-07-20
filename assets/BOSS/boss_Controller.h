#ifndef BOSS_CONTROLLER_H
#define BOSS_CONTROLLER_H

#include "boss_Head.h"
#include "boss_TailSegment.h"
#include "../terrain.h"
#include "../animation.h"
#include "../NAV/nav_graph.h"

class boss_Controller : public Object {
	private:
	terrain* ter;
	float tailWiggleAmplitude;
	float tailWiggleSpeed;
	Timer tailWiggleTimer;
	Vector2 tailOffset;
	Vector2 laserOffset;
	double idleAngle;
	boss_TailSegment* tail;
	AdvImage* laser;
	animation* laser_impact;
	animation* laser_impact2;
	AdvImage* laser_flare;
	void updateLaser();
	void updateTail();
	public:
		bool laserOn;
		nav_graph* bossNavigator;
		boss_Head* head;
		void draw();
		void update();
		boss_Controller(GameWindow* gw, terrain* ter);
		~boss_Controller();
		void setTailWiggle(float Amp, float Speed);
};



#endif // BOSS_CONTROLLER_H
