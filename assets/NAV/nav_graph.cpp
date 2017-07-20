#include "nav_graph.h"

nav_graph::nav_graph(Object* agent) {
	tl_in.set(-500, 1500);
	tl.set(130, 700);
	tl_out.set(130, -500);
	tl_in_control.set(500, 1200);

	tl_enter.init_bezier(tl_in, tl, tl_in_control, 0.01f, agent, false, true);
	tl_exit.init_sine(tl, tl_out, 170, 5, 0.005f, agent, true, false);

	tl2_out.set(-500, 800);
	tl2_out_control.set(0, 500);

	tl2_exit.init_bezier(tl, tl2_out, tl2_out_control, 0.02f, agent, true, false);

	//Example for linear: bl_t_tl.init_linear(bl, tl, 0.01f, agent, false, true);

	active = &tl_enter;
	location = OUT;
}

nav_graph::~nav_graph() {
}

void nav_graph::update() {
	active->update();
}

void nav_graph::moveTo(locations loc) {
	switch(loc) {
	case TL : {
		traverse(&tl_enter);
		break;
	}
	case TL2 : {
		traverse(&tl_enter);
		break;
	}
	case OUT : {
		if(location==TL) traverse(&tl_exit);
		if(location==TL2) traverse(&tl2_exit);
	}
	}
	location = loc;
}

bool nav_graph::isBusy() {
	return active->isBusy();
}

void nav_graph::traverse(nav_path* p) {
	p->traverse();
	active = p;
}
