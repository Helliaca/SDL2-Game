#ifndef NAV_GRAPH_H
#define NAV_GRAPH_H

#include "nav_path.h"

enum locations {TL, OUT, TL2};

class nav_graph {
	private:
		nav_path tl_enter; //bottom left to top left
		nav_path tl_exit;

		nav_path tl2_exit; //tl2 has same entry as tl

		Vector2 tl, tl_in, tl_out;
		Vector2 tl2_out, tl2_out_control;
		Vector2 tl_in_control;

		nav_path* active;
		locations location;

		void traverse(nav_path* p);
	public:
		nav_graph(Object* agent);
		~nav_graph();
		void moveTo(locations loc);
		void update();
		bool isBusy();
};



#endif // NAV_POINT_H
