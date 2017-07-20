#ifndef MISSILE_H
#define MISSILE_H

#include "physicsObj.h"
#include "animation.h"
#include "../random.h"

class missile : public AdvImage {
	private:
		Vector2 vel;
		Timer lifeTimer;
		animation* trail;
		Vector2 randomDrift;
		int randomDriftOffset;
		int randomDriftSpeed;
		Image* hitMarker;
		void setHitMarker(terrain* ter);
	public:
		animation* explosion;
		void update(terrain* ter);
		void draw();
		missile(GameWindow* gw);
		missile(GameWindow* gw, int spawnX, int spawnY, float velX, float velY, bool drop);
		~missile();
		void reset();
		void launch(Vector2 vel);
		bool dead;
		void setPos(Vector2 pos);
		Vector2 getPos();
		bool terrainCollision;
		bool flameTrail;
		bool straight;
		bool markHit;
		float lifetime;
};



#endif // MISSILE_H
