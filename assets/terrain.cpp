#include "terrain.h"

terrain::terrain(GameWindow* gw) : Image(gw) {
	//this->tex = SDL_CreateTexture(gw->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, SWIDTH, SHEIGHT);
	//SDL_Texture* tmp = IMG_LoadTexture(this->gw->renderer, TERRAIN1);

	terMask = IMG_Load("terrain1_msk.png");
	sur = IMG_Load("terrain1.png");
	updateTexture();
}

terrain::~terrain() {}

bool terrain::getSolid(int x, int y) {
	if(x>=LEVELWIDTH || y>=LEVELHEIGHT || x<=0 || y<=0) return true;
    SDL_LockSurface(sur);
    Uint32 color = get_pixel32(this->sur, x, y);
    SDL_UnlockSurface(sur);
    colorRGBA col;
    col.fromPixel32(color, sur->format);
    if(col.a>1) return true;
    return false;
}

bool terrain::getDestructible(int x, int y) {
	if(x>=LEVELWIDTH || y>=LEVELHEIGHT) return false;
	SDL_LockSurface(terMask);
	Uint32 color = get_pixel32(this->terMask, x, y);
	SDL_UnlockSurface(sur);
	colorRGBA col;
	col.fromPixel32(color, terMask->format);
	if(col.r>=255 && col.g==0 && col.b>=255) return false;
	return true;
}

void terrain::updateTexture() {
	this->tex = this->gw->textureFromSurface(sur);
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	this->texr.x = this->pos.x; texr.y = this->pos.y; texr.w = w; texr.h = h;
}

void terrain::explode(int x, int y, int r) {
	for(int i=x-r; i<x+r; i++) {
		for(int j=y-r; j<y+r; j++) {
			int distX = (i - x)*(i - x);
			int distY = (j - y)*(j - y);
			double distance = sqrt(distX + distY);
			if(distance<=r &&
					i<texr.w && i>0 &&
					j<texr.h && j>0 && getDestructible(i, j)) put_pixel32(sur, i, j, TRANSPARENT);
		}
	}
	updateTexture();
}

void terrain::create_square(Vector2 location, int r) {
	int x = location.x;
	int y = location.y;
	for(int i=x-r; i<x+r; i++) {
		for(int j=y-r; j<y+r; j++) {
			if(i<texr.w && i>0 &&
				j<texr.h && j>0 && getDestructible(i, j)) put_pixel32(sur, i, j, EARTH);
		}
	}
	updateTexture();
}

Vector2 terrain::raycast(Vector2 from, Vector2 dir, float skip) {
	dir.normalize();
	dir.mul(skip);
	while(!getSolid(from.x, from.y)) {
		from.add(dir);
	}
	return from;
}
