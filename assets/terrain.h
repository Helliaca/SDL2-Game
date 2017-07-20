#ifndef TERRAIN_H
#define TERRAIN_H

#include "../base.h"

class terrain : public Image {
	private:

	public:
		SDL_Surface *terMask;
		SDL_Surface *sur;
		terrain(GameWindow* gw);
		~terrain();
		bool getSolid(int x, int y);
		bool getDestructible(int x, int y);
		void updateTexture();
		void explode(int x, int y, int r);
		void create_square(Vector2 location, int r);
		Vector2 raycast(Vector2 from, Vector2 dir, float accuracy);
};



#endif // TERRAIN_H
