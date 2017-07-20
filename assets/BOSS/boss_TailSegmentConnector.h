#ifndef BOSS_TAILSEGMENTCONNECTOR_H
#define BOSS_TAILSEGMENTCOONECTOR_H

#include "../../base.h"

class boss_TailSegmentConnector : public AdvImage {
	private:
	public:
		void update(Vector2 from, Vector2 to);
		boss_TailSegmentConnector(GameWindow* gw);
		~boss_TailSegmentConnector();
};



#endif // BOSS_TAILSEGMENTCONNECTOR_H
