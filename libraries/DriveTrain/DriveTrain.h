#ifndef _DriveTrain_h
#define _DriveTrain_h

#include "Drive.h"

struct DriveTrainLayout {
	union {
		struct {
			byte leftTop, leftMid,	leftBack;
			byte rightTop, rightMid, rightBack;
			byte leftTopS, leftBotomS;
			byte rightTopS, rightBotomS;
		};
		struct {
			byte motorsLeft[3];
			byte motorsRight[3];
			byte servosLeft[2];
			byte servosRight[2];
		};
	};
};

typedef enum {MOTORL, MOTORR, SERVO, NA} State;

class Wheel {
	public:
	Wheel(byte, State);
	Wheel() {_id = 0; _msState = NA; }
	void forward(float);
	void backward(float);
	void turn(float);
	void stop();
	
	public:
	byte _id;
	State _msState;
};



#endif