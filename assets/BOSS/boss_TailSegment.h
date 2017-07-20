#ifndef BOSS_TAILSEGMENT_H
#define BOSS_TAILSEGMENT_H

#include "../../base.h"
#include "boss_TailSegmentConnector.h"

class boss_TailSegment : public AdvImage {
	private:
		Vector2 intenPos();
		double intenAngle();
		Vector2 vel, acel;
		double Avel, Aacel;
	public:
		boss_TailSegmentConnector* connector;
		Vector2 getMidUpperPoint();
		Vector2 getMidLowerPoint();
		boss_TailSegment* previous;
		boss_TailSegment* next;
		void update();
		void draw();
		boss_TailSegment(GameWindow* gw);
		~boss_TailSegment();
		void buildTail(int num, boss_TailSegment* prev);
};



#endif // BOSS_TAILSEGMENT_H
