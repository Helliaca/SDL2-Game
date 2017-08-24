#include "base.h"

using namespace std;


//=================GENERAL FUNCTIONS=========================

//Round a number to three decimals
double round_3dec(double val) {
	return round(val * 100.0 ) / 100.0;
}

//Get the color of a pixel on a surface
Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

//Set a pixel of a surface to a certain color
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

//Convert pixel color from number to actual color
void colorRGBA::fromPixel32(Uint32 pixel, const SDL_PixelFormat* format) {
	SDL_GetRGBA(pixel, format, &r, &g, &b, &a);
}

//Return smaller of two numbers
int min(int a, int b) {
	if(a<b) return a;
	return b;
}

//Return larger of two numbers
int max(int a, int b) {
	if(a>b) return a;
	return b;
}

//Clamp a number to a minimum and maximum
float clamp(float value, float min, float max) {
	if(value<min) return min;
	if(value>max) return max;
	return value;
}


//=================TIMER METHODS=========================

void Timer::start() {
	stime = (int)SDL_GetTicks();
}

int Timer::elapsedTime() {
	return ((int)SDL_GetTicks()) - stime;
}


//=================CAMERA AND GAMEWINDOW METHODS=========================

void Camera::setViewPortOffset(Vector2 vpo) {
	this->ViewPortOffset = vpo;
}

void Camera::follow(Vector2 pos) {
	centerOn(Lerp(getCenter(), pos, CAMERASMOOTHING));
}

void Camera::centerOn(Vector2 pos) {
	this->ViewPortOffset.x = clamp(pos.x - SWIDTH/2, 0, LEVELWIDTH-SWIDTH);
	this->ViewPortOffset.y = clamp(pos.y - SHEIGHT/2, 0, LEVELHEIGHT-SHEIGHT);
}

Vector2 Camera::getCenter() {
	Vector2 ret;
	ret.set(ViewPortOffset.x + SWIDTH/2, ViewPortOffset.y + SHEIGHT/2);
	return ret;
}

GameWindow::GameWindow(void) {
	renderer = NULL;
	win = NULL;
	camera = NULL;
	drawrect = NULL;
}

int GameWindow::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 0;
	win = SDL_CreateWindow(WINDOWNAME, 100, 100, SWIDTH, SHEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	camera = new Camera();
	camera->ViewPortOffset.x = camera->ViewPortOffset.y = 0;
	camera->ViewPortOffset.y = 300;
	drawrect = new SDL_Rect();
	return 1;
}

void GameWindow::draw(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
	drawrect->w = dstrect->w;
	drawrect->h = dstrect->h;
	drawrect->x = dstrect->x - camera->ViewPortOffset.x;
	drawrect->y = dstrect->y - camera->ViewPortOffset.y;
	SDL_RenderCopy(this->renderer, tex, srcrect, drawrect);
}

void GameWindow::draw(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
	drawrect->w = dstrect->w;
	drawrect->h = dstrect->h;
	drawrect->x = dstrect->x - camera->ViewPortOffset.x;
	drawrect->y = dstrect->y - camera->ViewPortOffset.y;
	SDL_RenderCopyEx(this->renderer, tex, srcrect, drawrect, angle, center, flip);
}

//The camera viewPortOffset will not be considered with the override functions
void GameWindow::drawOverride(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
	SDL_RenderCopy(this->renderer, tex, srcrect, dstrect);
}

void GameWindow::drawOverride(SDL_Texture* tex, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
	SDL_RenderCopyEx(this->renderer, tex, srcrect, dstrect, angle, center, flip);
}

//Convert a Surface to a Texture
SDL_Texture* GameWindow::textureFromSurface(SDL_Surface* sur) {
	return SDL_CreateTextureFromSurface(this->renderer, sur);
}

Vector2 GameWindow::getMousePosition() {
	Vector2 ret;
	int mx, my;
	SDL_GetMouseState(&mx, &my);
	ret.x = mx + camera->ViewPortOffset.x;
	ret.y = my + camera->ViewPortOffset.y;
	return ret;
}

void GameWindow::clear() {
	SDL_RenderClear(renderer);
}

void GameWindow::present() {
	SDL_RenderPresent(renderer);
}


//=================VECTOR2 METHODS=========================

Vector2::Vector2() {
	this->x = this->y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2::add(Vector2 v) {
	this->x += v.x;
	this->y += v.y;
}

void Vector2::add(float x, float y) {
	this->x += x;
	this->y += y;
}

void Vector2::sub(Vector2 v) {
	this->x -= v.x;
	this->y -= v.y;
}

void Vector2::sub(float x, float y) {
	this->x -= x;
	this->y -= y;
}

void Vector2::mul(float f) {
	this->x *= f;
	this->y *= f;
}

Vector2 Vector2::mul_N(float f) {
	Vector2 ret;
	ret.x = this->x*f;
	ret.y = this->y*f;
	return ret;
}

float Vector2::length() {
	return sqrt(x*x+y*y);
}

void Vector2::normalize() {
	float l = length();
	x = x/l;
	y = y/l;
}

double Vector2::angle(Vector2 v) { //Note that this function returns DEG
	double dot = this->x*v.x + this->y*v.y;
	double det = this->x*v.y - this->y*v.x;
	double ret = atan2(det, dot);
	ret *= (180.0/PI);
	while(ret<0) ret+=360;
	while(ret>360) ret-=360;
	return ret;
}

void Vector2::set(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2::fromAngle(double angle) { //Note that this function takes DEG arguments
	this->x = round_3dec(sin(angle*(PI/180.0)));
	this->y = round_3dec(cos((180-angle)*(PI/180.0))); //I honestly have no clue why I have to do 180-angle here, but it only works that way :D
	this->normalize();
}

void Vector2::rotate(double angle) { //takes deg argument
	angle = angle*(PI/180.0);
	float newX, newY;
    newX = x * cos(angle) - y * sin(angle);
    newY = x * sin(angle) + y * cos(angle);
    x = newX;
    y = newY;
}

//This is just a basic bezier function: http://answers.unity3d.com/questions/12689/moving-an-object-along-a-bezier-curve.html
Vector2 Bezier(Vector2 start, Vector2 control, Vector2 end, float t) {
	start.mul(((1-t)*(1-t)));
	control.mul(2 * t * (1 - t));
	end.mul((t * t));
	start.add(control);
	start.add(end);
	return start;
}

//Interpolates a Vector by value t
Vector2 Lerp(Vector2 start, Vector2 end, float t) {
	if(t<=0) return start;
	if(t>=1) return end;
	end.sub(start); //Vector from start to end
	end.mul(t);
	end.add(start);
	return end;
}

//Interpolates a float by value t
float Lerp(float start, float end, float t) {
	if(t<=0) return start;
	if(t>=1) return end;
	return (end-start)*t + start;
}


//=================OBJECT METHODS=========================

Object::Object(GameWindow* gw) {
	this->tag = DEFAULTTAG;
	this->gw = gw;
}

Object::~Object() {}

void Object::draw() {
}

void Object::init() {
	cout<<"Object Initialized"<<endl;
}

void Object::setPos(Vector2 pos) {
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

void Object::setPos(int x, int y) {
	this->pos.x = x;
	this->pos.y = y;
}

Vector2 Object::getPos() {
	return pos;
}


//=================IMAGE METHODS=========================

Image::Image(GameWindow* gw) : Object(gw) {
	tex = NULL;
	scale = 1;
}

Image::~Image() {
}

void Image::loadTexture(const char* path) {
	this->tex = IMG_LoadTexture(this->gw->renderer, path);
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	this->texr.x = this->pos.x; texr.y = this->pos.y; texr.w = w; texr.h = h;
}

void Image::draw() {
	gw->draw(this->tex, NULL, &texr);
}

void Image::update() {
	texr.x = pos.x;
	texr.y = pos.y;
}

SDL_Rect Image::getRect() {
	return this->texr;
}

void Image::setHeight(int h) {
	texr.h = h;
}

void Image::setPosCenter(Vector2 pos) {
	this->pos.x = pos.x - texr.w/2;
	this->pos.y = pos.y - texr.h/2;
}

void Image::setPosCenter(int x, int y){
	this->pos.x = x - texr.w/2;
	this->pos.y = y - texr.h/2;
}


//=================ADVIMAGE METHODS=========================

AdvImage::AdvImage(GameWindow* gw) : Image(gw) {
	flip = SDL_FLIP_NONE;
	center = NULL;
	angle = 0;
}

AdvImage::~AdvImage() {
}

void AdvImage::draw() {
	gw->draw(this->tex, NULL, &texr, angle, center, flip);
}

void AdvImage::setFromTo(Vector2 from, Vector2 to, bool height) {
	if(height) {
		Vector2 ft;
		Vector2 down;
		down.y=1;
		down.x=0;
		ft.x = to.x - from.x;
		ft.y = to.y - from.y;
		ft.x = -ft.x;
		this->texr.h = ft.length();
		this->angle = ft.angle(down);
		this->center->x = this->texr.w * 0.5f;
		this->pos = from;
		this->pos.x -= this->texr.w * 0.5f;
	}
	else {
		cout<<"setToFrom width not implemeted"<<endl;
	}
}

