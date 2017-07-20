#ifndef PLAYER_H
#define PLAYER_H

#include "physicsObj.h"
#include "animation.h"

class player : public physicsObj {
	private:
		animation* playerSprite;
	public:
		void update(terrain* ter);
		player(GameWindow* gw);
		~player();
		void draw();
		Vector2 getPos();
};



#endif // PLAYER_H
