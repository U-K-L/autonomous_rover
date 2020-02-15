#include "DriveTrain.h"

/* Wheel */
Wheel::Wheel(byte id, State type) {
	_id = id;
	_msState = type;
}

}

void Wheel::backward(float speed) {
	Driver::spinAt(_id, -speed);
}

void Wheel::turn(float angle) {
	Driver::moveTo(_id, angle);
}

void Wheel::stop() {
	Driver::spinAt(_id, 0);
}


/* DriveTrain */
void DriveTrain::setup() {
	 for(int i = 0; i < 3; i++) {
		wheels[i] = Wheel(layout.motorsLeft[i], MOTORL);
	 }
	 
	 for(int i = 3; i < 6; i++) {
		wheels[i] = Wheel(layout.motorsRight[i-3], MOTORR);
	 }
	 
	 Driver::setup();
}

void DriveTrain::forward(float speed) {
	for(int i = 0; i < 6; i++) {
		if(wheels[i]._msState == MOTORL) {
			wheels[i].forward(speed);
		}else if(wheels[i]._msState == MOTORR) {
			wheels[i].forward(-speed);
		}
	}
}

void DriveTrain::backward(float speed) {
	for(int i = 0; i < 6; i++) {
		if(wheels[i]._msState == MOTORL) {
			wheels[i].backward(speed);
		}else if(wheels[i]._msState == MOTORR) {
			wheels[i].backward(-speed);
		}
	}
}

void DriveTrain::stop() {
	for(int i = 0; i < 6; i++) {
		if(wheels[i]._msState == MOTORL) {
			wheels[i].stop();
		}else if(wheels[i]._msState == MOTORR) {
			wheels[i].stop();
		}
	}
}