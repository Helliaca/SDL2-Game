#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "physicsObj.h"

class projectile : public physicsObj {
	private:
		Image* projectileSprite;
	public:
		void update(terrain* ter);
		projectile(GameWindow* gw);
		~projectile();
		void draw();
		void die();
		void launch(Vector2 dir);
		bool dead;
		void setPos(Vector2 pos);
		Vector2 getPos();
};



#endif // PPRoJECTILE_H
