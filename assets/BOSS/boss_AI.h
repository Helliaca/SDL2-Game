#ifndef BOSS_AI_H
#define BOSS_AI_H

#include "boss_Controller.h"
#include "../../random.h"
#include "../missile.h"
#include <vector>

enum ATTACKS {LASER, ROCKETS, NONE};

class boss_AI : Object {
	private:
		vector<missile*> missiles;
		vector<missile*> rockets_drop;
		Timer innerTimer;
		Timer rocketDropTimer;
		bool busy;
		ATTACKS currentAttack;
		int innerStage;
		boss_Controller* boss;
		terrain* ter;

		void laser();

	public:
		bool spawnRockets;
		bool isBusy();
		void update();
		void draw();
		void launchAttack(ATTACKS a);
		boss_AI(GameWindow* gw, terrain* ter);
		~boss_AI();
};



#endif // BOSS_AI_H
