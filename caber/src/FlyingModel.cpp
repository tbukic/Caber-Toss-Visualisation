/*
 * FlyingModel.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#include "FlyingModel.h"

FlyingModel::FlyingModel() :
		MotionModel() {
}

void FlyingModel::delta_speed(CaberMotion const & caber,
		std::array<double, 3> & delta) {
	delta[DELTA_X_AXIS_SPEED] = 0.0;
	delta[DELTA_Y_AXIS_SPEED] = -GRAVITY;
	delta[DELTA_ANGULAR_SPEED] = 0.0;
}

void FlyingModel::caber_changed(Caber const &) {
}
