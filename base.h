#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cmath>

#include "defs.h"

using namespace std;

Uint32 get_pixel32( SDL_Surface *surface, int x, int y );
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
double round_3dec(double val);
float clamp(float value, float min, float max);

class colorRGBA {
	public:
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 a;
		void fromPixel32(Uint32 pixel, const SDL_PixelFormat* format);
};

//====================================================================

class Timer {
	private:
		int stime;
	public:
		void start();
		int elapsedTime();
};

//====================================================================

class Vector2 {
	public:
		float x, y;
		Vector2();
		Vector2(float x, float y);
		void sub(Vector2 v);
		void sub(float x, float y);
		void add(Vector2 v);
		void add(float x, float y);
		void mul(float f);
		Vector2 mul_N(float f);
		void normalize();
		float length();
		double angle(Vector2 v);
		void set(float x, float y);
		void fromAngle(double angle);
		void rotate(double angle);
};

Vector2 Bezier(Vector2 start, Vector2 control, Vector2 end, float t);

Vector2 Lerp(Vector2 start, Vector2 end, float t);

float Lerp(float start, float end, float t);

//====================================================================

class Camera {
	public:
		Vector2 ViewPortOffset;
		void setViewPortOffset(Vector2 vpo);
		void centerOn(Vector2 pos);
		void follow(Vector2 pos);
		Vector2 getCenter();
};

class GameWindow {
	private:
		int nothing;
		SDL_Rect* drawrect;
	public:
		Camera* camera;
		SDL_Window *win = NULL;
		SDL_Renderer *renderer = NULL;
		SDL_Texture* textureFromSurface(SDL_Surface* sur);
		void draw(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
		void draw(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);
		void drawOverride(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect);
		void drawOverride(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip);
		Vector2 getMousePosition();
		GameWindow();
		int init();
};

//====================================================================

class Object {
	protected:
		GameWindow* gw;
		char tag;
		Vector2 pos;
	public:
		void setPos(Vector2 pos);
		void setPos(int x, int y);
		Vector2 getPos();
		void draw();
		void init();
		Object(GameWindow* gw);
		~Object();
};

//====================================================================

class Image : public Object {
	protected:
		SDL_Texture* tex;
		SDL_Rect texr;
	public:
		float scale;
		SDL_Rect getRect();
		void setPosCenter(Vector2 pos);
		void setPosCenter(int x, int y);
		void setHeight(int h);
		void draw();
		void loadTexture(const char* path);
		void update();
		Image(GameWindow* gw);
		~Image();
};

//====================================================================

class AdvImage : public Image {
	protected:
	public:
		double angle;
		SDL_Point* center;
		SDL_RendererFlip flip;
		void draw();
		void setFromTo(Vector2 from, Vector2 to, bool height);
		AdvImage(GameWindow* gw);
		~AdvImage();
};

#endif // BASE_H
