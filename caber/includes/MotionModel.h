/*
 * MotionModel.h
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#ifndef SRC_MOTIONMODEL_H_
#define SRC_MOTIONMODEL_H_

#include "CaberMotion.h"
#include "Caber.h"
#include <cmath>
#include <array>
#include <cstddef>
#include <memory>

class MotionModel {
public:
	using size_type = std::size_t;
	static const double GRAVITY;
	const static size_type DELTA_X_AXIS_SPEED;
	const static size_type DELTA_Y_AXIS_SPEED;
	const static size_type DELTA_ANGULAR_SPEED;
	virtual void delta_speed(CaberMotion const & caber,
			std::array<double, 3> & delta) = 0;
	MotionModel();
	void set_caber(Caber const &);
	virtual ~MotionModel();
protected:
	virtual void caber_changed(Caber const &) = 0;
};

#endif /* SRC_MOTIONMODEL_H_ */
