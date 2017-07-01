/*
 * RunningModel.h
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#ifndef SRC_RUNNINGMODEL_H_
#define SRC_RUNNINGMODEL_H_

#include "MotionModel.h"
#include "Caber.h"

class RunningModel: public MotionModel {
public:
	RunningModel();
	void set_acceleration(double);
	void delta_speed(CaberMotion const & caber, std::array<double, 3> & delta);
	virtual ~RunningModel() {
	}
protected:
	void caber_changed(Caber const &);
private:
	double v_acceleration;
	double constant_coefficient;
};

#endif /* SRC_RUNNINGMODEL_H_ */
