/*
 * CaberMotion.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: motangens
 */

#include "CaberMotion.h"

#include <stdexcept>
#include <string>
#include <math.h>

const CaberMotion::size_type CaberMotion::X_AXIS_COORDINATE = 0;
const CaberMotion::size_type CaberMotion::Y_AXIS_COORDINATE = 1;
const CaberMotion::size_type CaberMotion::ANGLE = 2;
const CaberMotion::size_type CaberMotion::X_AXIS_SPEED = 3;
const CaberMotion::size_type CaberMotion::Y_AXIS_SPEED = 4;
const CaberMotion::size_type CaberMotion::ANGULAR_SPEED = 5;
const CaberMotion::data_type CaberMotion::MINIMAL_X_AXIS_VALUE = 0;
const CaberMotion::data_type CaberMotion::MINIMAL_Y_AXIS_VALUE = 0;
const CaberMotion::data_type CaberMotion::MINIMAL_ANGLE_VALUE = 0;
const CaberMotion::data_type CaberMotion::MAXIMAL_ANGLE_VALUE = M_PI;

CaberMotion::CaberMotion(data_type initial_x_axis, data_type initial_y_axis,
		data_type initial_angle) {
	if (initial_x_axis < MINIMAL_X_AXIS_VALUE) {
		throw std::invalid_argument(
				"X-axis value can not be negative. Inserted: "
						+ std::to_string(initial_x_axis));
	}
	if (initial_y_axis < MINIMAL_Y_AXIS_VALUE) {
		throw std::invalid_argument(
				"Y-axis value can not be negative. Inserted: "
						+ std::to_string(initial_y_axis));
	}
	if (initial_angle < MINIMAL_ANGLE_VALUE
			|| initial_angle > MAXIMAL_ANGLE_VALUE) {
		throw std::invalid_argument(
				"Angle has to be between 0 and PI. Inserted: "
						+ std::to_string(initial_angle));
	}
	x_coord() = initial_x_axis;
	y_coord() = initial_y_axis;
	angle() = initial_angle;
	x_speed() = y_speed() = angular_speed() = 0;
}

CaberMotion::~CaberMotion() {
}

std::ostream& operator<<(std::ostream& out, const CaberMotion & caber) {
	bool not_first = false;
	out << "[";
	for (CaberMotion::data_type data : caber.data) {
		if (not_first) {
			out << ", ";
		} else {
			not_first = true;
		}
		out << data;
	}
	out << "]";
	return out;
}
