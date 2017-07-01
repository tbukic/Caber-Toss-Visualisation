/*
 * CaberMotion.h
 *
 *  Created on: Nov 18, 2015
 *      Author: motangens
 */

#ifndef SRC_CABERMOTION_H_
#define SRC_CABERMOTION_H_

#include <array>
#include <cstddef>
#include <memory>
#include <ostream>

/**
 * Class models caber in motion in 2D grid.
 *
 * It keeps data about caber's X and Y coordinate, it's angle FI,
 * and about it's speed in those 3 directions.
 *
 * It offers direct and named access to the data.
 */
class CaberMotion {
public:
	using data_type = double;
	using size_type = std::size_t;
	/**
	 * Number of accessible data positions.
	 */
	const static size_type SIZE = 6;
	/**
	 * Index of X coordinate of the caber.
	 */
	const static size_type X_AXIS_COORDINATE;
	/**
	 * Index of Y coordinate of the caber.
	 */
	const static size_type Y_AXIS_COORDINATE;
	/**
	 * Index of caber's angle.
	 */
	const static size_type ANGLE;
	/**
	 * Index of caber's speed in x direction.
	 */
	const static size_type X_AXIS_SPEED;
	/**
	 * Index of caber's speed in y direction.
	 */
	const static size_type Y_AXIS_SPEED;
	/**
	 * Index of caber's angular speed.
	 */
	const static size_type ANGULAR_SPEED;

	const static data_type MINIMAL_X_AXIS_VALUE;
	const static data_type MINIMAL_Y_AXIS_VALUE;
	const static data_type MINIMAL_ANGLE_VALUE;
	const static data_type MAXIMAL_ANGLE_VALUE;

	CaberMotion(data_type initial_x_axis, data_type initial_y_axis,
			data_type initial_angle);

	inline data_type & operator[](size_type position) {
		if (position < 0 || position >= SIZE) {
			throw std::out_of_range("Undefined element.");
		}
		return data[position];
	}

	inline data_type & x_coord() {
		return data[X_AXIS_COORDINATE];
	}
	inline data_type & y_coord() {
		return data[Y_AXIS_COORDINATE];
	}
	inline data_type & angle() {
		return data[ANGLE];
	}
	inline data_type const & angle() const {
			return data[ANGLE];
		}
	inline data_type & x_speed() {
		return data[X_AXIS_SPEED];
	}
	inline data_type & y_speed() {
		return data[Y_AXIS_SPEED];
	}
	inline data_type & angular_speed() {
		return data[ANGULAR_SPEED];
	}
	inline data_type const & angular_speed() const {
		return data[ANGULAR_SPEED];
	}

	virtual ~CaberMotion();

	friend std::ostream& operator<<(std::ostream&, const CaberMotion &);
private:
	/**
	 * Keeps data about caber and it's movement.
	 */
	std::array<data_type, SIZE> data;
};

#endif /* SRC_CABERMOTION_H_ */
