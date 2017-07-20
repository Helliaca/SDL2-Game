#include "projectile.h"

projectile::projectile(GameWindow* gw) : physicsObj(gw) {
	projectileSprite = new Image(gw);
	projectileSprite->loadTexture(PROJECTILESPRITE);
	this->setCol(projectileSprite->getRect().w, projectileSprite->getRect().h);
	this->friction = false;
	this->gravity = false;
	dead = false;
}

projectile::~projectile() {
	delete(projectileSprite);
}

void projectile::update(terrain* ter) {
	if(dead) return;
	if(grounded(ter) || leftCol(ter) || rightCol(ter)) {
		ter->explode(pos.x+this->col.x/2, pos.y+this->col.y/2, 50);
		dead = true;
	}
	physicsObj::update(ter);
	projectileSprite->setPos(this->pos);
	projectileSprite->update();
}

void projectile::draw() {
	projectileSprite->draw();
}

void projectile::setPos(Vector2 pos) {
	this->pos = pos;
}

Vector2 projectile::getPos() {
	return this->pos;
}

void projectile::launch(Vector2 dir) {
	dir.add(-pos.x, -pos.y);
	dir.normalize();
	dir.mul(8); //speed
	this->accelerate(dir.x, dir.y);
}
