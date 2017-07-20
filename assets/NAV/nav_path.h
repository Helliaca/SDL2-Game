#ifndef NAV_PATH_H
#define NAV_PATH_H

#include "../../base.h"

enum interpolation_mode {LINEAR, SINE, BEZIER};

class nav_path {
	private:
		float relPos; //Percentage positioning along the path
		float speed;
		float sine_amplitude;
		float sine_curveamount;
		Vector2 bezier_control;
		bool easeIn;
		bool easeOut;
	public:
		bool active;
		Object* agent;
		interpolation_mode mode;
		Vector2 start;
		Vector2 end;
		nav_path();
		~nav_path();
		void init_linear(Vector2 start, Vector2 end, float speed, Object* agent, bool easeIn, bool easeOut);
		void init_sine(Vector2 start, Vector2 end, float amp, float mul, float speed, Object* agent, bool easeIn, bool easeOut);
		void init_bezier(Vector2 start, Vector2 end, Vector2 control, float speed, Object* agent, bool easeIn, bool easeOut);
		void traverse();
		void update();
		bool isBusy();
};



#endif // NAV_POINT_H
