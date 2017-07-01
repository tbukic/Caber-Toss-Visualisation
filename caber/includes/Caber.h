/*
 * Caber.h
 *
 *  Created on: Nov 18, 2015
 *      Author: motangens
 */

#ifndef SRC_CABER_H_
#define SRC_CABER_H_

/**
 * Class models physical appearance of the caber.
 */
class Caber {
public:
	const double & mass() const;
	const double & length() const;
	Caber(double mass, double length);
	virtual ~Caber();
private:
	double mass_data;
	double length_data;
};

#endif /* SRC_CABER_H_ */
