/*
 * Caber.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: motangens
 */

#include "Caber.h"
#include <stdexcept>
#include <string>

const double & Caber::mass() const {
	return mass_data;
}

const double & Caber::length() const {
	return length_data;
}

Caber::Caber(double mass, double length) :
		mass_data(mass), length_data(length) {
	if (mass <= 0) {
		throw std::invalid_argument(
				"Mass must be positive. Inserted: "
						+ std::to_string(mass_data));
	}
	if (length <= 0) {
		throw std::invalid_argument(
				"Length must be positive. Inserted: "
						+ std::to_string(length_data));
	}
}

Caber::~Caber() {
}
