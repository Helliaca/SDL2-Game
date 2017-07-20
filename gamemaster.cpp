#include <iostream>
#include "gamemaster.h"
#include "assets/terrain.h"
#include "assets/player.h"
#include "assets/projectile.h"
#include "assets/animation.h"
#include "assets/background.h"
#include "assets/BOSS/boss_AI.h"

GameWindow* win = new GameWindow();

Timer frametimer;
Timer projtimer;

Vector2 mousePos;

vector<Object*> objs; //<- this doesn't work
vector<projectile*> projs;
vector<animation*> anims;
void drawAllObjs();
void drawAllProjs();
void drawAllAnims();
void updateAllProjs(terrain*);
void updateAllAnims();


void start() {
	win->init();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(IMG_INIT_PNG);

	background* bg = new background(win);
	bg->loadTexture(BACKGROUND1);

	terrain* o = new terrain(win);

	player* p = new player(win);

	boss_AI* b = new boss_AI(win, o);

	frametimer.start();
	projtimer.start();
	while(1) {
		mousePos = win->getMousePosition();
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		SDL_Event e;
		if ( SDL_PollEvent(&e) ) {
			if (e.type == SDL_QUIT)	break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) break;
			else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1) {
				b->launchAttack(LASER);
			}
			else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_2) {
				b->launchAttack(ROCKETS);
			}
			else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_3) {
				b->launchAttack(ROCKETS_DROP);
			}
		}

		//b->setPos(mousePos);
		win->camera->follow(p->getPos());

		if(SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_GetMouseState(NULL, NULL)) == 8) o->create_square(mousePos, 25); // looks like right mouse button is 8. SDL_BUTTON_RIGHT seems to be broken
		if(SDL_MOUSEBUTTONDOWN && SDL_BUTTON(SDL_GetMouseState(NULL, NULL)) == SDL_BUTTON_LEFT && projtimer.elapsedTime()>300) {
			projectile* np = new projectile(win);
			np->setPos(p->getPos());
			np->launch(mousePos);
			projs.push_back(np);
			projtimer.start();
		}
		if (keys[SDL_SCANCODE_W]) p->accelerate(0,-PLAYER_ACCEL_Y);
		if (keys[SDL_SCANCODE_S]) p->accelerate(0,PLAYER_ACCEL_Y);
		if (keys[SDL_SCANCODE_D]) p->accelerate(PLAYER_ACCEL_X,0);
		if (keys[SDL_SCANCODE_A]) p->accelerate(-PLAYER_ACCEL_X,0);
		//if (keys[SDL_SCANCODE_R]) b->head->tilt(1);
		//if (keys[SDL_SCANCODE_T]) b->head->tilt(-1);

		SDL_RenderClear(win->renderer);

		//Draw everything
		bg->draw();
		p->draw();
		o->draw();
		drawAllProjs();
		drawAllAnims();
		b->draw();
		//drawAllObjs(); //<- this doesnt work :(

		SDL_RenderPresent(win->renderer);

		//Update objects dependant on frametime
		updateAllAnims();
		b->update();
		p->update(o);
		bg->update(win->camera->ViewPortOffset);
		updateAllProjs(o);

		while(frametimer.elapsedTime()<MIN_FRAMETIME) SDL_Delay(1); //Really low frametimes ruin physics :(
		frametimer.start();
	}
	SDL_Delay(5000);
}

void drawAllAnims() {
	for(int i=0; i<anims.size(); i++) {
		anims[i]->draw();
	}
}

void drawAllObjs() {
	for(int i=0; i<objs.size(); i++) {
		objs[i]->draw();
	}
}

void drawAllProjs() {
	for(int i=0; i<projs.size(); i++) {
		projs[i]->draw();
	}
}

void updateAllProjs(terrain* ter) {
	for(int i=0; i<projs.size(); i++) {
		if(projs[i]->dead) {
			//spawn animation
			animation* onDeath = new animation(win);
			onDeath->setPos(projs[i]->getPos().x, projs[i]->getPos().y);
			onDeath->setAnim(EXPLOSIONSPRITE, 4, 4, 50, 1);
			anims.push_back(onDeath);
			//remove projectile
			delete projs[i];
			projs.erase(projs.begin()+i-1);
			i--;
		}
		projs[i]->update(ter);
	}
}

void updateAllAnims() {
	for(int i=0; i<anims.size(); i++) {
		if(anims[i]->dead) {
					delete anims[i];
					anims.erase(anims.begin()+i-1);
					i--;
		}
		anims[i]->update();
	}
}

