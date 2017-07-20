#ifndef PHYSICSOBJ_H
#define PHYSICSOBJ_H

#include "../base.h"
#include "terrain.h"

class physicsObj : public Object {
	protected:
		Vector2 col;
		Vector2 vel;
	public:
		void setCol(float x, float y);
		physicsObj(GameWindow* gw);
		//~physicsObj();
		void update(terrain* ter);
		void accelerate(float x, float y);
		bool gravity;
		bool friction;
		bool grounded(terrain* ter);
		bool leftCol(terrain* ter);
		bool rightCol(terrain* ter);
};



#endif // PHYSICSOBJ_H
