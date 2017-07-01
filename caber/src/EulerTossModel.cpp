/*
 * TossModel.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: motangens
 */

#include <cmath>
#include "EulerTossModel.h"
#include <stdexcept>
#include <string>
#include <array>
#include <iostream>

const double EulerTossModel::MAX_RUNNING_DISTANCE = 7;
const double EulerTossModel::MAX_THROW_HORIZONTAL = 0.5;
const double EulerTossModel::MAX_THROW_VERTICAL = 0.75;
const double EulerTossModel::EPSILON = 0.01;
const int EulerTossModel::DIVERGENCE_TRASHOLD = 50;
const int EulerTossModel::DEFAULT_BUFFER_SIZE = 1000;

EulerTossModel::EulerTossModel(double delta_time) :
		running_model(), throw_model(), fly_model(), landing_model(), v_delta_time(
				delta_time), divergence_count(0), recorder(nullptr), recording(
				EulerTossModel::TypeOfRecording::nothing) {
	if (delta_time <= 0) {
		std::invalid_argument(
				"Time interval must have strictly positive value. Inserted: "
						+ std::to_string(delta_time));
	}
}

void EulerTossModel::set_caber(Caber const & caber) {
	running_model.set_caber(caber);
	throw_model.set_caber(caber);
	fly_model.set_caber(caber);
	landing_model.set_caber(caber);
}

void EulerTossModel::move_caber_next_step(CaberMotion & caber,
		double x_speed_change, double y_speed_change,
		double angular_speed_change) {
	caber.x_coord() += (caber.x_speed() * v_delta_time);
	caber.y_coord() += (caber.y_speed() * v_delta_time);
	caber.angle() += (caber.angular_speed() * v_delta_time);
	caber.x_speed() += (x_speed_change * v_delta_time);
	caber.y_speed() += (y_speed_change * v_delta_time);
	caber.angular_speed() += (angular_speed_change * v_delta_time);
}

double calculate_y_at_other_end(CaberMotion & caber_motion,
		Caber const & caber_physics) {
	return caber_motion.y_coord()
			+ caber_physics.length() * sin(caber_motion.angle());
}

bool EulerTossModel::ground_touched(CaberMotion & caber_motion,
		Caber const & caber_physics) const {
	const double y1 = caber_motion.y_coord();
	const double y2 = calculate_y_at_other_end(caber_motion, caber_physics);
	return (y1 <= 0) || (y2 <= 0);
}

bool EulerTossModel::evaluate(CaberMotion & caber,
		Caber const & caber_physics) {
	divergence_count = 0.0;
	std::array<double, 3> delta_speed = { 0.0, 0.0, 0.0 };
	CaberMotion original_copy(caber);
	set_caber(caber_physics);

	auto do_one_step =
			[&](MotionModel & model,
					std::string const & phase) {
				model.delta_speed(caber, delta_speed);
				move_caber_next_step(caber, delta_speed[MotionModel::DELTA_X_AXIS_SPEED],
						delta_speed[MotionModel::DELTA_Y_AXIS_SPEED],
						delta_speed[MotionModel::DELTA_ANGULAR_SPEED]);
				if (is_recording_everything()) {
					recorder->record_line(phase, caber);
				}
			};

	const std::string RUNNING_PHASE = "running";
	//std::cout << RUNNING_PHASE << std::endl;
	double throw_location = caber.x_coord() + MAX_RUNNING_DISTANCE;
	while (caber.x_coord() < throw_location) {
		do_one_step(running_model, RUNNING_PHASE);
		if (ground_touched(caber, caber_physics) || diverged(delta_speed)) {
			return false;
		}

	}

	std::string THROWING_PHASE = "throwing";
	//std::cout << THROWING_PHASE << std::endl;
	const double max_x = caber.x_coord() + MAX_THROW_VERTICAL, max_y =
			caber.y_coord() + MAX_THROW_HORIZONTAL;
	while (max_x > caber.x_coord() && max_y > caber.y_coord()
			&& !ground_touched(caber, caber_physics)) {
		do_one_step(throw_model, THROWING_PHASE);
		if (diverged(delta_speed)) {
			return false;
		}
	}

	const std::string FLYING_PHASE = "flying";
	//std::cout << FLYING_PHASE << std::endl;
	while (!ground_touched(caber, caber_physics)) {
		do_one_step(fly_model, FLYING_PHASE);
		if (diverged(delta_speed)) {
			throw std::logic_error("Critical error, caber doens't fall.");
		}
	}

	// landing phase:
	// switching coordinate systems.
	caber.x_speed() = 0.0;
	caber.y_speed() = 0.0;
	double other_end = calculate_y_at_other_end(caber, caber_physics);
	if (other_end < caber.y_coord()) {
		caber.y_coord() = other_end;
	} else {
		return false;
	}

	const std::string LANDING_PHASE = "landing";
	while (sin(caber.angle()) < 0) {
		do_one_step(landing_model, LANDING_PHASE);
		if (diverged(delta_speed)) {
			return false;
		}
	}

	bool successful = cos(caber.angle()) < 0.0;
	if (is_recording_sucessfull()) {
		recorder->record_attempt(original_copy);
	}
	return successful;
}

bool EulerTossModel::diverged(std::array<double, 3> const & deltas) {
	double deltas_squared_sum = 0.0;
	for (auto value : deltas) {
		deltas_squared_sum += pow(value, 2);
	}
	divergence_count =
			(deltas_squared_sum < EPSILON ? divergence_count + 1 : 0);
	return divergence_count > DIVERGENCE_TRASHOLD;
}

void EulerTossModel::start_recording(std::unique_ptr<Recorder> & precorder, TypeOfRecording type) {
	if (precorder == nullptr) {
		throw std::runtime_error("No pointer to recorder given.");
	}
	recorder = precorder.release();
	recording = type;
}

void EulerTossModel::start_recording(std::string to_file,
		unsigned int buffer_size, EulerTossModel::TypeOfRecording type) {
	stop_recording();
	if (type != EulerTossModel::TypeOfRecording::sucessfull
			&& type != EulerTossModel::TypeOfRecording::everything) {
		throw std::runtime_error("Bad type of recording given.");
	}
	recording = type;
	try {
		recorder = new ModelRecorder(to_file, buffer_size);
	} catch (std::runtime_error & error) {
		if (nullptr != recorder) {
			delete recorder;
			recorder = nullptr;
		}
		throw error;
	}
}

void EulerTossModel::start_recording(std::string to_file,
		EulerTossModel::TypeOfRecording type) {
	start_recording(to_file, ModelRecorder::BUFFER_INITIAL_SIZE, type);
}

bool EulerTossModel::is_recording() {
	return (nullptr != recorder);
}

bool EulerTossModel::is_recording_sucessfull() {
	return (recording == EulerTossModel::TypeOfRecording::sucessfull);
}

bool EulerTossModel::is_recording_everything() {
	return (recording == EulerTossModel::TypeOfRecording::everything);
}

unsigned int EulerTossModel::buffer_size() {
	if (!is_recording()) {
		return 0;
	}
	return recorder->buffer_size();
}

unsigned long EulerTossModel::stop_recording() {
	if (nullptr == recorder) {
		return 0L;
	}
	recording = EulerTossModel::TypeOfRecording::nothing;
	unsigned long recorded = recorder->stop_recording();
	delete recorder;
	recorder = nullptr;
	return recorded;
}

void EulerTossModel::set_acceleration(double acceleration) {
	running_model.set_acceleration(acceleration);
}
void EulerTossModel::set_vertical_force(double vertical_force) {
	throw_model.set_vertical_force(vertical_force);
}
void EulerTossModel::set_horizontal_force(double horizontal_force) {
	throw_model.set_horizontal_force(horizontal_force);
}

EulerTossModel::~EulerTossModel() {
	stop_recording();
}

const int ModelRecorder::BUFFER_INITIAL_SIZE = 1000;
const int ModelRecorder::BUFFER_INITIAL_EXCEPTED_LINE_LENGTH = 50;

ModelRecorder::ModelRecorder(std::string const & file_name,
		unsigned int buffer_size)
try :
		is_recording(false), buff_size(buffer_size), recorded(0L), buffer_taken(
				0), excepted_line_length(BUFFER_INITIAL_EXCEPTED_LINE_LENGTH) {
	if (buffer_size <= 0) {
		throw std::runtime_error(
				"Buffer size must be positive! Inserted"
						+ std::to_string(buffer_size));
	}
	file.open(file_name.c_str());
	is_recording = true;
	buffer.reserve(buff_size * excepted_line_length);
}
catch (std::exception & e) {
	throw std::runtime_error(
			e.what() + std::string("\nError in opening file!"));
}

ModelRecorder::ModelRecorder(std::string const & file_name) :
		ModelRecorder(file_name, BUFFER_INITIAL_SIZE) {
}
;

void ModelRecorder::flush_buffer() {
	if (!is_recording) {
		throw std::logic_error("Can't flush buffer when not recording!");
	}

	file << buffer;

	unsigned int excepted_buff_length = buff_size * excepted_line_length;
	if (buffer.length() > excepted_buff_length) {
		excepted_line_length = buffer.length() / buff_size + 10;
		excepted_buff_length = buff_size * excepted_line_length;
	}

	buffer.clear();
	buffer.reserve(excepted_buff_length);
	buffer_taken = 0;
}

unsigned long ModelRecorder::stop_recording() {
	if (!is_recording) {
		return 0L;
	}
	if (buff_size > 0) {
		flush_buffer();
	}
	file.close();
	is_recording = false;
	long rec = recorded;
	recorded = 0L;
	return rec;
}

unsigned int ModelRecorder::buffer_size() {
	return buff_size;
}

void ModelRecorder::record_line(std::string const & phase,
		CaberMotion & caber) {
	check_is_recording();
	buffer = buffer + std::to_string(recorded++) + "," + phase;
	record_caber(caber);
}

void ModelRecorder::record_attempt(CaberMotion & caber) {
	check_is_recording();
	buffer = buffer + std::to_string(recorded++);
	record_caber(caber);
}

void ModelRecorder::record_caber(CaberMotion & caber) {
	for (CaberMotion::size_type index = 0; index < CaberMotion::SIZE; ++index) {
		buffer = buffer + "," + std::to_string(caber[index]);
	}
	buffer.append("\n");
	if (++buffer_taken >= buff_size) {
		flush_buffer();
	}
}

void ModelRecorder::check_is_recording() {
	if (!is_recording) {
		throw std::runtime_error("Recording ended.");
	}
}

ModelRecorder::~ModelRecorder() {
	stop_recording();
}
