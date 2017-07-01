/*
 * TossModel.h
 *
 *  Created on: Nov 18, 2015
 *      Author: motangens
 */

#ifndef SRC_EULERTOSSMODEL_H_
#define SRC_EULERTOSSMODEL_H_

#include <memory>
#include "CaberMotion.h"
#include "RunningModel.h"
#include "ThrowModel.h"
#include "FlyingModel.h"
#include "LandingModel.h"
#include <fstream>

class Recorder {
public:
	virtual void record_line(std::string const &, CaberMotion &) = 0;
	virtual void record_attempt(CaberMotion &) = 0;
	virtual unsigned long stop_recording() = 0;
	virtual unsigned int buffer_size() = 0;
	virtual ~Recorder() {
	};
};

class ModelRecorder : public Recorder {
public:
	static const int BUFFER_INITIAL_SIZE;
	static const int BUFFER_INITIAL_EXCEPTED_LINE_LENGTH;
	ModelRecorder(std::string const &);
	ModelRecorder(std::string const &, unsigned int);
	unsigned int buffer_size();
	void record_line(std::string const &, CaberMotion &);
	void record_attempt(CaberMotion &);
	unsigned long stop_recording();
	~ModelRecorder();
private:
	void flush_buffer();
	void record_caber(CaberMotion &);
	void check_is_recording();
	bool is_recording;
	unsigned int buff_size;
	unsigned long recorded;
	unsigned int buffer_taken;
	unsigned int excepted_line_length;
	std::string buffer;
	std::ofstream file;
};

class EulerTossModel {
public:
	enum TypeOfRecording {
		nothing, sucessfull, everything
	};

	const static double MAX_RUNNING_DISTANCE;
	const static double MAX_THROW_HORIZONTAL;
	const static double MAX_THROW_VERTICAL;
	const static double EPSILON;
	const static int DIVERGENCE_TRASHOLD;
	const static int DEFAULT_BUFFER_SIZE;

	EulerTossModel(double delta_time);

	EulerTossModel(EulerTossModel &) = delete;
	EulerTossModel(EulerTossModel &&) = delete;
	EulerTossModel & operator=(EulerTossModel &) = delete;
	EulerTossModel & operator=(EulerTossModel &&) = delete;

	virtual ~EulerTossModel();
	void set_acceleration(double);
	void set_vertical_force(double);
	void set_horizontal_force(double);
	/**
	 * Returns true if toss was successful (after landing, angle =-PI), or false in other cases.
	 */
	bool evaluate(CaberMotion &, Caber const &);
	bool ground_touched(CaberMotion &, Caber const &) const;
	bool diverged(std::array<double, 3> const &);

	void start_recording(std::unique_ptr<Recorder> &, EulerTossModel::TypeOfRecording);
	void start_recording(std::string to_file, EulerTossModel::TypeOfRecording);
	void start_recording(std::string to_file, unsigned int buffer_size, EulerTossModel::TypeOfRecording);
	bool is_recording();
	unsigned long stop_recording();
	unsigned int buffer_size();
private:
	void set_caber(Caber const &);
	void move_caber_next_step(CaberMotion & caber, double x_speed_change,
			double y_speed_change, double angular_speed_change);
	bool is_recording_sucessfull();
	bool is_recording_everything();
	RunningModel running_model;
	ThrowModel throw_model;
	FlyingModel fly_model;
	LandingModel landing_model;
	double v_delta_time;
	int divergence_count;
	Recorder * recorder;
	EulerTossModel::TypeOfRecording recording;
};

#endif /* SRC_TOSSMODEL_H_ */
