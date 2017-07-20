#ifndef ANIMATION_H
#define ANIMATION_H

#include "../base.h"

class animation : public Image {
	private:
		Timer* innerTimer;
		int rows, cols, dir;
		float deltaT;
		int currFrame, maxFrame;
		SDL_Rect srcRect;
	public:
		bool loop;
		bool dieOnEnd;
		bool dead;
		bool manualOverride;
		void setFrame(int framenum);
		void setAnim(const char* path, int rows, int columns, float deltaT, int direction);
		void update();
		animation(GameWindow* gw);
		~animation();
		void setPos(float x, float y);
		void draw();
		void reset();
};



#endif // PLAYER_H
