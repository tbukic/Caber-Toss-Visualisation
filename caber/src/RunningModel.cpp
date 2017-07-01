/*
 * RunningModel.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#include "RunningModel.h"
#include <string>
#include <stdexcept>

RunningModel::RunningModel() :
		MotionModel(), v_acceleration(0.0), constant_coefficient(0.0) {
}
void RunningModel::set_acceleration(double acceleration) {
	if (acceleration <= 0) {
		throw std::invalid_argument(
				"Acceleration has to be positive. Inserted: "
						+ std::to_string(acceleration));
	}
	v_acceleration = acceleration;
}

void RunningModel::caber_changed(Caber const & caber) {
	constant_coefficient = (3.0 / 2.0) / caber.length();
}

void RunningModel::delta_speed(CaberMotion const & caber, std::array<double, 3> & delta) {
	delta[DELTA_X_AXIS_SPEED] = v_acceleration;
	delta[DELTA_Y_AXIS_SPEED] = 0;
	delta[DELTA_ANGULAR_SPEED] = constant_coefficient
					* (v_acceleration * sin(caber.angle())
							- GRAVITY * cos(caber.angle()));

}
