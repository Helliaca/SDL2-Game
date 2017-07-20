#include "boss_AI.h"

boss_AI::boss_AI(GameWindow* gw, terrain* ter) : Object(gw) {
	boss = new boss_Controller(gw, ter);
	busy = false;
	currentAttack = NONE;
	innerStage = 0;
	this->ter = ter;
	for(int i=0; i<30; i++) {
		missiles.push_back(new missile(this->gw, 0, 0, ROCKET_SPEED, 0, false));
		missiles.at(i)->dead = true;
	}
	rocketDropTimer.start();
}

boss_AI::~boss_AI() {
}

void boss_AI::update() {
	boss->update();
	for(int i = missiles.size()-1; i>=0; i--) {
		 missiles.at(i)->update(ter);
	}
	for(int i = rockets_drop.size()-1; i>=0; i--) {
		 rockets_drop.at(i)->update(ter);
		 if(rockets_drop.at(i)->explosion->dead) {
			 missile* m = rockets_drop.at(i);
			 rockets_drop.erase(rockets_drop.begin() + i);
			 delete m;
			 i--;
		 }
	}

	if(rocketDropTimer.elapsedTime() > 500) {
		missile* m = new missile(this->gw, getRandInteger(300,LEVELWIDTH), 100, 0, ROCKET_SPEED*3, true);
		rockets_drop.push_back(m);
		rocketDropTimer.start();
	}

	switch(currentAttack) {
		case LASER : {
			if(innerStage<=0) { //Move boss to position
				boss->bossNavigator->moveTo(TL);
				innerStage = 1;
			}
			else if(innerStage==1 && !boss->bossNavigator->isBusy()) { //Boss at position, go to next stage
				innerTimer.start();
				innerStage = 2;
			}
			else if(innerStage==2) {	//Move head to -20deg
				boss->head->setTilt(Lerp(0, -20, innerTimer.elapsedTime()/200.0f));
				if(innerTimer.elapsedTime()>=200.0) {
					boss->laserOn = true;
					boss->head->laser = true;
					boss->setTailWiggle(1.5f, 1.2f);
					innerTimer.start();
					innerStage = 3;
				}
			}
			else if(innerStage==3) {	//Move laser up to down
				boss->head->setTilt(Lerp(-20, 60, innerTimer.elapsedTime()/BOSS_LASER_DURATION));
				if(innerTimer.elapsedTime()>=BOSS_LASER_DURATION) {
					innerTimer.start();
					innerStage = 4;
				}
			}
			else if(innerStage==4) {	//Move laser back up
				boss->head->setTilt(Lerp(60, -20, innerTimer.elapsedTime()/BOSS_LASER_DURATION));
				if(innerTimer.elapsedTime()>=BOSS_LASER_DURATION) {
					boss->laserOn = false;
					boss->head->laser = false;
					innerTimer.start();
					boss->setTailWiggle(1.0f, 1.0f);
					boss->bossNavigator->moveTo(OUT);
					innerStage = 5;
				}
			}
			else if(innerStage==5) {	//Move head to default position and bugger off
				boss->head->setTilt(Lerp(-20, 0, innerTimer.elapsedTime()/500.0f));
				if(!boss->bossNavigator->isBusy()) innerStage = 6;
			}
			else if(innerStage==6) {	//Boss arrived outside, end attack
				launchAttack(NONE);
			}
			break;
		}

		case ROCKETS : {
			if(innerStage<=0) { //Move boss to position
				boss->bossNavigator->moveTo(TL2);
				innerStage = 1;
			}
			else if(innerStage==1 && !boss->bossNavigator->isBusy()) { //Increase Tail movement
				boss->setTailWiggle(2.0f, 1.0f);
				boss->head->setIdleOffsetMul(5.0, 2.0);
				innerTimer.start();
				//spawn rockets
				Vector2 spawnPos;
				spawnPos.set(-530, 700);
				for(int i=0; i<missiles.size()/3; i++) {missiles.at(i)->setPos(spawnPos); spawnPos.y += 80; missiles.at(i)->reset();}
				spawnPos.set(-930, 200);
				for(int i=missiles.size()/3; i<2*missiles.size()/3; i++) {missiles.at(i)->setPos(spawnPos); spawnPos.y += 80; missiles.at(i)->reset();}
				spawnPos.set(-1330, 700);
				for(int i=2*missiles.size()/3; i<missiles.size(); i++) {missiles.at(i)->setPos(spawnPos); spawnPos.y += 80; missiles.at(i)->reset();}
				innerStage = 2;
			}
			else if(innerStage==2 && innerTimer.elapsedTime()>5000.0f) {	//bugger off
				boss->setTailWiggle(1.0f, 1.0f);
				boss->head->setIdleOffsetMul(1.0, 1.0);
				boss->bossNavigator->moveTo(OUT);
				innerStage = 5;
				innerTimer.start();
			}
			else if(innerStage==5) {	//Move head to default position and bugger off
				boss->head->setTilt(Lerp(0, -120, innerTimer.elapsedTime()/500.0f));
				if(!boss->bossNavigator->isBusy()) innerStage = 6;
			}
			else if(innerStage==6 && !boss->bossNavigator->isBusy()) {	//Boss arrived outside, end attack
				boss->head->setTilt(0);
				launchAttack(NONE);
			}
			break;
		}

	}

}

void boss_AI::launchAttack(ATTACKS a) {
	currentAttack = a;
	innerStage = 0;
}

void boss_AI::draw() {
	for(int i = missiles.size()-1; i>=0; i--) {
		missiles.at(i)->draw();
	}
	for(int i = rockets_drop.size()-1; i>=0; i--) {
		rockets_drop.at(i)->draw();
	}
	boss->draw();
}
