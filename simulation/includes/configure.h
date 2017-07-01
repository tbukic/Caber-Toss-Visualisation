#ifndef CONFIGURE_H_INCLUDED
#define CONFIGURE_H_INCLUDED

#include <string>
#include <memory>

class Configuration;

class Configure {
private:
	const static std::string SEPARATOR, SHEIGHT, SWIDTH, DTIME,
		MASS_MIN, MASS_MAX, MASS_DEF, MASS_UNIT, MASS_TITLE,
		ANGLE_MIN, ANGLE_MAX, ANGLE_DEF, ANGLE_UNIT, ANGLE_TITLE,
		ACC_MIN, ACC_MAX, ACC_DEF, ACC_UNIT, ACC_TITLE,
		HFORCE_MIN, HFORCE_MAX, HFORCE_DEF, HFORCE_UNIT, HFORCE_TITLE,
		VFORCE_MIN, VFORCE_MAX, VFORCE_DEF, VFORCE_UNIT, VFORCE_TITLE,
		HEIGHT_MIN, HEIGHT_MAX, HEIGHT_DEF, HEIGHT_UNIT, HEIGHT_TITLE,
		TH_HEIGHT_MIN, TH_HEIGHT_MAX, TH_HEIGHT_DEF, TH_HEIGHT_UNIT,
		TH_HEIGHT_TITLE, CCOLOR, BACKGROUND_SRC, FONT_PATH, SCALE_ANGLE_RANGE;
	std::unique_ptr<Configuration> conf;
	void store(std::string, std::string);
public:
	Configure();
	std::unique_ptr<Configuration> const & configuration();
	Configuration * release_configuration();
	void set_default();
	void read(std::string);
	void write(std::string);
	~Configure();
};

class Configuration {
private:
	int v_screen_heigth, v_screen_width;
	double v_delta_time, v_scale_angle_range,
		v_caber_mass_min, v_caber_mass_max, v_caber_mass_def,
		v_caber_angle_min, v_caber_angle_max, v_caber_angle_def,
		v_caber_acc_min, v_caber_acc_max, v_caber_acc_def,
		v_caber_hforce_min, v_caber_hforce_max, v_caber_hforce_def,
		v_caber_vforce_min, v_caber_vforce_max, v_caber_vforce_def,
		v_caber_height_min, v_caber_height_max, v_caber_height_def,
		v_thrower_height_min, v_thrower_height_max, v_thrower_height_def;
	std::string v_caber_color, v_background_src, v_font_path, v_mass_unit,
		 v_height_unit, v_thrower_height_unit, v_angle_unit, v_acc_unit,
		 v_hforce_unit, v_vforce_unit,
		 v_mass_title, v_height_title, v_thrower_height_title, v_angle_title,
		 v_acc_title, v_hforce_title, v_vforce_title;
	
public:
	int screen_heigth() const;
	int screen_width() const;
	double delta_time() const;
	double scale_angle_range() const;
	double caber_mass_min() const;
	double caber_mass_max() const;
	double caber_mass_def() const;
	double caber_height_min() const;
	double caber_height_max() const;
	double caber_height_def() const;
	double thrower_height_min() const;
	double thrower_height_max() const;
	double thrower_height_def() const;
	double caber_angle_min() const;
	double caber_angle_max() const;
	double caber_angle_def() const;
	double caber_acc_min() const;
	double caber_acc_max() const;
	double caber_acc_def() const;
	double caber_hforce_min() const;
	double caber_hforce_max() const;
	double caber_hforce_def() const;
	double caber_vforce_min() const;
	double caber_vforce_max() const;
	double caber_vforce_def() const;
	std::string caber_color() const;
	std::string background_src() const;
	std::string font_path() const;
	std::string mass_unit() const;
	std::string height_unit() const;
	std::string thrower_height_unit() const;
	std::string angle_unit() const;
	std::string acc_unit() const;
	std::string hforce_unit() const;
	std::string vforce_unit() const;
	std::string mass_title() const;
	std::string height_title() const;
	std::string thrower_height_title() const;
	std::string angle_title() const;
	std::string acc_title() const;
	std::string hforce_title() const;
	std::string vforce_title() const;

	
	friend Configure;
};

#endif // CONFIGURE_H_INCLUDED
