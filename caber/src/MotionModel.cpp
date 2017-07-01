/*
 * MotionModel.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#include "MotionModel.h"
#include <stdexcept>

const double MotionModel::GRAVITY = 9.81;
const MotionModel::size_type MotionModel::DELTA_X_AXIS_SPEED = 0;
const MotionModel::size_type MotionModel::DELTA_Y_AXIS_SPEED = 1;
const MotionModel::size_type MotionModel::DELTA_ANGULAR_SPEED = 2;

MotionModel::MotionModel() {
}

void MotionModel::set_caber(Caber const & caber) {
	caber_changed(caber);
}

MotionModel::~MotionModel() {
}
