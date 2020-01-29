#pragma once
#include <math.h>
static double toDegrees(double a) {
	return a * (180 / M_PI);
}

static double toRadians(double a) {
	return a * (M_PI /180);
}