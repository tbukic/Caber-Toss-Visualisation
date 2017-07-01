#include "configure.h"

#include <fstream>
#include <set>

const std::string Configure::SEPARATOR = " = ";
const std::string Configure::SHEIGHT = "screen height";
const std::string Configure::SWIDTH = "screen width";
const std::string Configure::DTIME = "delta time";
const std::string Configure::MASS_MIN = "mass_min";
const std::string Configure::MASS_MAX = "mass_max";
const std::string Configure::MASS_DEF = "mass_def";
const std::string Configure::MASS_UNIT = "mass unit";
const std::string Configure::MASS_TITLE = "set mass title";
const std::string Configure::HEIGHT_MIN = "height_min";
const std::string Configure::HEIGHT_MAX = "height_max";
const std::string Configure::HEIGHT_DEF = "height_def";
const std::string Configure::HEIGHT_UNIT = "height unit";
const std::string Configure::HEIGHT_TITLE = "set height title";
const std::string Configure::TH_HEIGHT_MIN = "thrower_height_min";
const std::string Configure::TH_HEIGHT_MAX = "thrower_height_max";
const std::string Configure::TH_HEIGHT_DEF = "thrower_height_def";
const std::string Configure::TH_HEIGHT_UNIT = "thrower_height unit";
const std::string Configure::TH_HEIGHT_TITLE = "set thrower height title";

const std::string Configure::ACC_MIN = "acc_min";
const std::string Configure::ACC_MAX = "acc_max";
const std::string Configure::ACC_DEF = "acc_def";
const std::string Configure::ACC_UNIT = "acc unit";
const std::string Configure::ACC_TITLE = "set acc title";

const std::string Configure::HFORCE_MIN = "hforce_min";
const std::string Configure::HFORCE_MAX = "hforce_max";
const std::string Configure::HFORCE_DEF = "hforce_def";
const std::string Configure::HFORCE_UNIT = "hforce unit";
const std::string Configure::HFORCE_TITLE = "set hforce title";

const std::string Configure::VFORCE_MIN = "vforce_min";
const std::string Configure::VFORCE_MAX = "vforce_max";
const std::string Configure::VFORCE_DEF = "vforce_def";
const std::string Configure::VFORCE_UNIT = "vforce unit";
const std::string Configure::VFORCE_TITLE = "set vforce title";

const std::string Configure::ANGLE_MIN = "angle_min";
const std::string Configure::ANGLE_MAX = "angle_max";
const std::string Configure::ANGLE_DEF = "angle_def";
const std::string Configure::ANGLE_UNIT = "angle unit";
const std::string Configure::ANGLE_TITLE = "set angle title";
const std::string Configure::CCOLOR = "caber_rgb";
const std::string Configure::BACKGROUND_SRC = "background_pic source";
const std::string Configure::FONT_PATH = "font path";
const std::string Configure::SCALE_ANGLE_RANGE = "scale angle range";

Configure::Configure() :
	conf(new Configuration()) {
	set_default();
}

Configure::~Configure() {
}

std::unique_ptr<Configuration> const & Configure::configuration() {
	return conf;
}

Configuration * Configure::release_configuration() {
	Configuration * tmp = conf.release();
	conf = std::unique_ptr<Configuration>(new Configuration());
	return tmp;
}

void Configure::set_default() {
	conf->v_screen_heigth = 200;
	conf->v_screen_width = 400;
	conf->v_delta_time = 0.01;
	write("default.conf");
}

void Configure::store(std::string key, std::string value) {
	if (SHEIGHT == key) {
		conf->v_screen_heigth = std::stoi(value);
	} else if (SWIDTH == key) {
		conf->v_screen_width = std::stoi(value);
	} else if (DTIME == key) {
		conf->v_delta_time = std::stod(value);
	} else if (MASS_MIN == key) {
		conf->v_caber_mass_min = std::stod(value);
	} else if (MASS_MAX == key) {
		conf->v_caber_mass_max = std::stod(value);
	} else if (MASS_DEF == key) {
		conf->v_caber_mass_def = std::stod(value);
	} else if (HEIGHT_MIN == key) {
		conf->v_caber_height_min = std::stod(value);
	} else if (HEIGHT_MAX == key) {
		conf->v_caber_height_max = std::stod(value);
	} else if (HEIGHT_DEF == key) {
		conf->v_caber_height_def = std::stod(value);
	}else if (TH_HEIGHT_MIN == key) {
		conf->v_thrower_height_min = std::stod(value);
	} else if (TH_HEIGHT_MAX == key) {
		conf->v_thrower_height_max = std::stod(value);
	} else if (TH_HEIGHT_DEF == key) {
		conf->v_thrower_height_def = std::stod(value);
	} else if (CCOLOR == key) {
		conf->v_caber_color = value;
	} else if (BACKGROUND_SRC == key) {
		conf->v_background_src = value;
	} else if (FONT_PATH == key) {
		conf->v_font_path = value;
	} else if (MASS_UNIT == key) {
		conf->v_mass_unit = value;
	} else if (HEIGHT_UNIT == key) {
		conf->v_height_unit = value;
	} else if (TH_HEIGHT_UNIT == key) {
		conf->v_thrower_height_unit = value;
	} else if (MASS_TITLE == key) {
		conf->v_mass_title = value;
	} else if (HEIGHT_TITLE == key) {
		conf->v_height_title = value;
	} else if (TH_HEIGHT_TITLE == key) {
		conf->v_thrower_height_title = value;
	} else if (SCALE_ANGLE_RANGE == key) {
		conf->v_scale_angle_range = std::stod(value);
	} else if (ANGLE_MIN == key) {
		conf->v_caber_angle_min = std::stod(value);
	} else if (ANGLE_MAX == key) {
		conf->v_caber_angle_max = std::stod(value);
	} else if (ANGLE_DEF == key) {
		conf->v_caber_angle_def = std::stod(value);
	} else if (ANGLE_UNIT == key) {
		conf->v_angle_unit = value;
	} else if (ANGLE_TITLE == key) {
		conf->v_angle_title = value;
	} else if (ACC_MIN == key) {
		conf->v_caber_acc_min = std::stod(value);
	} else if (ACC_MAX == key) {
		conf->v_caber_acc_max = std::stod(value);
	} else if (ACC_DEF == key) {
		conf->v_caber_acc_def = std::stod(value);
	} else if (ACC_UNIT == key) {
		conf->v_acc_unit = value;
	} else if (ACC_TITLE == key) {
		conf->v_acc_title = value;
	} else if (HFORCE_MIN == key) {
		conf->v_caber_hforce_min = std::stod(value);
	} else if (HFORCE_MAX == key) {
		conf->v_caber_hforce_max = std::stod(value);
	} else if (HFORCE_DEF == key) {
		conf->v_caber_hforce_def = std::stod(value);
	} else if (HFORCE_UNIT == key) {
		conf->v_hforce_unit = value;
	} else if (HFORCE_TITLE == key) {
		conf->v_hforce_title = value;
	} else if (VFORCE_MIN == key) {
		conf->v_caber_vforce_min = std::stod(value);
	} else if (VFORCE_MAX == key) {
		conf->v_caber_vforce_max = std::stod(value);
	} else if (VFORCE_DEF == key) {
		conf->v_caber_vforce_def = std::stod(value);
	} else if (VFORCE_UNIT == key) {
		conf->v_vforce_unit = value;
	} else if (VFORCE_TITLE == key) {
		conf->v_vforce_title = value;
	}
}

void Configure::read(std::string file_name) {
	std::ifstream file;
	file.open(file_name);
	if (!file.is_open()) {
		throw std::runtime_error("File does not exist.");
	
	}
	std::string line;
	size_t sep;
	std::string key, value;
	std::set<std::string> keys;
	while (std::getline(file, line)) {
		sep = line.find(SEPARATOR);
		if (sep == std::string::npos) {
			throw std::runtime_error("Badly formated file. No separator.");
		}
		key = line.substr(0, sep);
		value = line.substr(sep + SEPARATOR.size());
		if (keys.find(key) != keys.end()) {
			throw std::runtime_error("Badly formated file. Duplicate key.");
		}
		keys.insert(key);
		store(key, value);
	}
	file.close();
}

void Configure::write(std::string file_name) {
	std::ofstream file(file_name);
	if (!file.is_open()) {
		throw std::runtime_error("Error in saving configuration.");
	}
	file << SHEIGHT << SEPARATOR << conf->screen_heigth() << std::endl;
	file << SWIDTH << SEPARATOR << conf->screen_width() << std::endl;
	file << DTIME << SEPARATOR << conf->delta_time() << std::endl;
	file.close();
}

int Configuration::screen_heigth() const {
	return v_screen_heigth;
}
int Configuration::screen_width() const {
	return v_screen_width;
}
double Configuration::delta_time() const {
	return v_delta_time;
}
double Configuration::scale_angle_range() const {
	return v_scale_angle_range;
}
double Configuration::caber_mass_min() const {
	return v_caber_mass_min;
} 
double Configuration::caber_mass_max() const {
	return v_caber_mass_max;
}
double Configuration::caber_mass_def() const {
	return v_caber_mass_def;
}
double Configuration::caber_height_min() const {
	return v_caber_height_min;
}
double Configuration::caber_height_max() const {
	return v_caber_height_max;
}
double Configuration::caber_height_def() const {
	return v_caber_height_def;
}
double Configuration::thrower_height_min() const {
	return v_thrower_height_min;
}
double Configuration::thrower_height_max() const {
	return v_thrower_height_max;
}
double Configuration::thrower_height_def() const {
	return v_thrower_height_def;
}
std::string Configuration::caber_color() const {
	return v_caber_color;
}
std::string Configuration::background_src() const {
	return v_background_src;
}
std::string Configuration::font_path() const {
	return v_font_path;
}
std::string Configuration::mass_unit() const {
	return v_mass_unit;
}
std::string Configuration::height_unit() const {
	return v_height_unit;
}
std::string Configuration::thrower_height_unit() const {
	return v_thrower_height_unit;
}
std::string Configuration::mass_title() const {
	return v_mass_title;
}
std::string Configuration::height_title() const {
	return v_height_title;
}
std::string Configuration::thrower_height_title() const {
	return v_thrower_height_title;
}

double Configuration::caber_acc_min() const {
	return v_caber_acc_min;
}
double Configuration::caber_acc_max() const {
	return v_caber_acc_max;
}
double Configuration::caber_acc_def() const {
	return v_caber_acc_def;
}
std::string Configuration::acc_unit() const {
	return v_acc_unit;
}
std::string Configuration::acc_title() const {
	return v_acc_title;
}


double Configuration::caber_angle_min() const {
	return v_caber_angle_min;
}
double Configuration::caber_angle_max() const {
	return v_caber_angle_max;
}
double Configuration::caber_angle_def() const {
	return v_caber_angle_def;
}
std::string Configuration::angle_unit() const {
	return v_angle_unit;
}
std::string Configuration::angle_title() const {
	return v_angle_title;
}


double Configuration::caber_hforce_min() const {
	return v_caber_hforce_min;
}
double Configuration::caber_hforce_max() const {
	return v_caber_hforce_max;
}
double Configuration::caber_hforce_def() const {
	return v_caber_hforce_def;
}
std::string Configuration::hforce_unit() const {
	return v_hforce_unit;
}
std::string Configuration::hforce_title() const {
	return v_hforce_title;
}


double Configuration::caber_vforce_min() const {
	return v_caber_vforce_min;
}
double Configuration::caber_vforce_max() const {
	return v_caber_vforce_max;
}
double Configuration::caber_vforce_def() const {
	return v_caber_vforce_def;
}
std::string Configuration::vforce_unit() const {
	return v_vforce_unit;
}
std::string Configuration::vforce_title() const {
	return v_vforce_title;
}
