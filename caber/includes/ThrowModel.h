/*
 * ThrowModel.h
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#ifndef SRC_THROWMODEL_H_
#define SRC_THROWMODEL_H_

#include "MotionModel.h"
#include <cmath>

class ThrowModel: public MotionModel {
public:
	ThrowModel();
	~ThrowModel() {
	}
	void set_horizontal_force(double);
	void set_vertical_force(double);
	void delta_speed(CaberMotion const & caber, std::array<double, 3> & delta);
protected:
	void caber_changed(Caber const &);
private:
	void check_nonpositive_force(double);
	double v_horizontal_force;
	double v_vertical_force;
	double v_mass;
	double v_half_length;
	double v_two_thirds_length;
	double v_horizontal_over_mass;
	double v_vertical_over_mass;
};

#endif /* SRC_THROWMODEL_H_ */
