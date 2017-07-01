/*
 * LandingModel.h
 *
 *  Created on: Nov 19, 2015
 *      Author: motangens
 */

#ifndef SRC_LANDINGMODEL_H_
#define SRC_LANDINGMODEL_H_

#include "MotionModel.h"
class LandingModel: public MotionModel {
public:
	LandingModel();
	void delta_speed(CaberMotion const & caber, std::array<double, 3> & delta);
	~LandingModel() {
	}
protected:
	void caber_changed(Caber const &);
private:
	double v_double_length;
};

#endif /* SRC_LANDINGMODEL_H_ */
