/*
 * ThrowModel.cpp
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#include "ThrowModel.h"
#include <stdexcept>

/**
 * Sets everything to initial values which are incorrect, but which won't destroy the program.
 */
ThrowModel::ThrowModel() :
		v_horizontal_force(0.0), v_vertical_force(0.0), v_mass(1.0), v_half_length(
				1.0), v_two_thirds_length(1.0), v_horizontal_over_mass(0.0), v_vertical_over_mass(
				0.0) {
}
void ThrowModel::set_horizontal_force(double horizontal_force) {
	check_nonpositive_force(horizontal_force);
	v_horizontal_force = horizontal_force;
	v_horizontal_over_mass = v_horizontal_force / v_mass;
}
void ThrowModel::set_vertical_force(double vertical_force) {
	check_nonpositive_force(vertical_force);
	v_vertical_force = vertical_force;
	v_vertical_over_mass = v_vertical_force / v_mass;
}
void ThrowModel::caber_changed(Caber const & caber) {
	v_half_length = caber.length() / 2.0;
	v_two_thirds_length = 3.0 / 2.0 * caber.length();
	v_mass = caber.mass();
	v_horizontal_over_mass = v_horizontal_force / v_mass;
	v_vertical_over_mass = v_vertical_force / v_mass;
}

void ThrowModel::check_nonpositive_force(double force) {
	if (force <= 0) {
		std::invalid_argument(
				"Force must have positive value. Inserted: "
						+ std::to_string(force));
	}
}

void ThrowModel::delta_speed(CaberMotion const & caber,
		std::array<double, 3> & delta) {
	const double SINE_ANGLE = sin(caber.angle());
	const double COSINE_ANGLE = cos(caber.angle());
	const double half_x_sqr_angle_speed = 2.0 * pow(caber.angular_speed(), 2.0);

	delta[DELTA_ANGULAR_SPEED] = (v_vertical_over_mass * COSINE_ANGLE
			+ half_x_sqr_angle_speed * COSINE_ANGLE * SINE_ANGLE)
			/ (v_half_length * pow(COSINE_ANGLE, 2.0) - v_two_thirds_length);

	const double HELP_VARIABLE_1 = v_half_length * delta[DELTA_ANGULAR_SPEED];
	const double HELP_VARIABLE_2 = half_x_sqr_angle_speed * SINE_ANGLE;
	delta[DELTA_X_AXIS_SPEED] = v_horizontal_over_mass + HELP_VARIABLE_1
			+ HELP_VARIABLE_2;
	delta[DELTA_Y_AXIS_SPEED] = v_vertical_over_mass - GRAVITY - HELP_VARIABLE_1
			+ HELP_VARIABLE_2;
}
