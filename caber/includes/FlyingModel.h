/*
 * FlyingModel.h
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#ifndef SRC_FLYINGMODEL_H_
#define SRC_FLYINGMODEL_H_

#include "MotionModel.h"

class FlyingModel: public MotionModel {
public:
	FlyingModel();
	void delta_speed(CaberMotion const & caber, std::array<double, 3> & delta);
	~FlyingModel() {
	}
protected:
	void caber_changed(Caber const &);
};

#endif /* SRC_FLYINGMODEL_H_ */
