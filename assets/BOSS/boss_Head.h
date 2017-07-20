#ifndef BOSS_HEAD_H
#define BOSS_HEAD_H

#include "../../base.h"

class boss_Head : public AdvImage {
	private:
		AdvImage* alt;
		double idleAngle;
		Vector2 idleOffset;
		Vector2 idleOffsetMul;
	public:
		bool laser;
		boss_Head(GameWindow* gw);
		~boss_Head();
		void update();
		void tilt(double angle);
		void setTilt(double angle);
		void setIdleOffsetMul(float x, float y);
		void draw();
};



#endif // BOSS_HEAD_H
