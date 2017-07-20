#include "player.h"

player::player(GameWindow* gw) : physicsObj(gw) {
	playerSprite = new animation(gw);
	playerSprite->setAnim(PLAYERSPRITE, 3, 3, -1, 1);
	this->setCol(playerSprite->getRect().w, playerSprite->getRect().h);
	this->pos.set(200,500);
}

player::~player() {
	delete(playerSprite);
}

void player::update(terrain* ter) {
	physicsObj::update(ter);

	if(this->vel.x>MOVE_ANIM_VEL && this->vel.y>MOVE_ANIM_VEL) playerSprite->setFrame(2);
	else if(this->vel.x<-MOVE_ANIM_VEL && this->vel.y>MOVE_ANIM_VEL) playerSprite->setFrame(0);
	else if(this->vel.x>MOVE_ANIM_VEL) playerSprite->setFrame(5);
	else if(this->vel.x<-MOVE_ANIM_VEL) playerSprite->setFrame(3);
	else if(this->vel.y>MOVE_ANIM_VEL) playerSprite->setFrame(1);
	else playerSprite->setFrame(4);


	playerSprite->setPos(this->pos.x, this->pos.y);
	playerSprite->update();
}

void player::draw() {
	playerSprite->draw();
}

Vector2 player::getPos() {
	return this->pos;
}
