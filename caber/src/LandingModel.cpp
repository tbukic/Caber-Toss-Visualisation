/*
 * LandingModel.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#include "LandingModel.h"

LandingModel::LandingModel() :
		MotionModel(), v_double_length(1.0) {
}

void LandingModel::caber_changed(Caber const & caber) {
	v_double_length = 2.0 * caber.length();
}

void LandingModel::delta_speed(CaberMotion const & caber,
		std::array<double, 3> & delta) {
	delta[DELTA_X_AXIS_SPEED] = 0.0;
	delta[DELTA_Y_AXIS_SPEED] = 0.0;
	delta[DELTA_ANGULAR_SPEED] = -3.0 * GRAVITY * cos(caber.angle())
			/ v_double_length;
}
