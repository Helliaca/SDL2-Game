#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../base.h"

class background : public Image {
	private:
		Vector2 moveDistance;
	public:
		background(GameWindow* gw);
		~background();
		void update(Vector2 CameraPos);
		void draw();
};



#endif // BACKGROUND_H
