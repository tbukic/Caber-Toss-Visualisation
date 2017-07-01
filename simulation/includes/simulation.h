#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

#include "EulerTossModel.h"
#include "Caber.h"
#include "CaberMotion.h"
#include "configure.h"

class Record {
public:
	Record() = default;
	Record(std::string const &, double, double, double);
	std::string get_phase() const;
	double get_x() const;
	double get_y() const;
	double get_angle() const;
private:
	std::string m_phase;
	double m_x, m_y, m_angle;
};

class SimRecorder : public Recorder {
public:
	SimRecorder();
	virtual void record_line(std::string const &, CaberMotion &);
	virtual void record_attempt(CaberMotion &);
	virtual unsigned long stop_recording();
	virtual unsigned int buffer_size();
	virtual ~SimRecorder();
	std::vector<Record> const & get_records() const;
private:
	std::vector<Record> m_recorded; 
};

class SceneNode;

class Scene {
public:
	using EventFunction = std::function<void(sf::Event &)>;
	using ProcessEvents = std::vector<Scene::EventFunction>;
	virtual ~Scene();
};

class ScaleNode;
class CaberShape;

class Simulation : public Scene {
public:
	Simulation(std::unique_ptr<Configuration> const &);
	void run();

private:
	const static double PI;
	bool m_not_closed;
	sf::RenderWindow m_window;
	std::unique_ptr<ScaleNode> m_scale;
	std::unique_ptr<CaberShape> m_caber_shape;
	std::unique_ptr<Caber> m_caber;
	std::unique_ptr<CaberMotion> m_caber_motion;
	std::unique_ptr<EulerTossModel> m_toss_model;
	sf::Texture m_background;
	sf::Font m_font;
	bool m_font_loaded;
	std::vector<SceneNode *> m_sceneGraph;
	std::string m_set_mass_title, m_set_mass_unit, m_set_height_title, m_set_height_unit,
	m_set_acc_title, m_set_acc_unit, m_set_hforce_title, m_set_hforce_unit,
	m_set_vforce_title, m_set_vforce_unit, m_thrower_height_title, m_thrower_height_unit,
	m_angle_title, m_angle_unit;
	double m_delta_time, m_min_mass, m_max_mass, m_cur_mass, m_min_height,
		m_max_height, m_cur_height,
		m_min_acc, m_max_acc, m_cur_acc, m_min_hforce, m_max_hforce, m_cur_hforce,
		m_min_vforce, m_max_vforce, m_cur_vforce,
		m_thrower_min_height, m_thrower_max_height, m_thrower_cur_height,
		m_min_angle, m_max_angle, m_cur_angle, m_caber_width_coef;
	
	void set_caber();
	void set_toss();
	void toss_caber();
	
	double use_scale(std::string const &, std::string const &, double, double, double);
	
	void process_events(ProcessEvents & );
	void render();
};

class SceneNode : public sf::Transformable,
		public sf::Drawable,
		private sf::NonCopyable {
public:
	virtual void draw(
		sf::RenderTarget& target, 
		sf::RenderStates states
	) const = 0;
	virtual void process_event(sf::Event &) = 0;
};

class CaberShape : public SceneNode {
public:
	CaberShape(float width, float height, std::string color);
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
	void updateAngle(float angleRad);
	void updateSize(float, float);
	static void parse_color(std::string &, int &, int &, int &);
	virtual void process_event(sf::Event &);
private:
	sf::RectangleShape shape;
	float m_width, m_height;
	int windowWidth, windowHeight;
};

class BackgroundNode : public SceneNode {
public:
	BackgroundNode(sf::Texture const &);
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
	virtual void process_event(sf::Event &);
private:
	sf::Sprite m_picture;
};

class ScaleNode : public SceneNode {
public:
	ScaleNode(sf::RenderWindow &, sf::Font &, double, double = 0.8);
	double normalize(double);
	void set(std::string const & title, std::string const & metric_unit, double min_value, double def_value, double max_value);
	virtual void process_event(sf::Event &);
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
	double to_deg(double);
	bool is_done() const;
	void reset_scale();
	double get_current_value() const;
	const static double TO_DEG_COEF;
private:
	const static double RADIUS, BORDER_LINE_LEN, HALF_LINE_LEN,
		TICK_LEN, THICK_COEF, UPDATE_COEF;
	
	const static sf::Color & FILL_COLOR, & OUTLINE_COLOR, & TICK_COLOR;
	
	bool m_not_set, m_done, m_mouse_held;
	sf::RenderWindow & m_window;
	double m_angle_range, m_min_value, m_max_value, m_cur_value, m_ratio;
	int m_dim;
	double m_center_x, m_center_y;
	
	std::string m_title_text, m_metric_unit;
	
	sf::Text m_title;
	
	sf::CircleShape m_scale_circle;
	
	sf::RectangleShape m_scale_min, m_scale_max, m_scale_mid, m_scale_tick;
	
	std::string s;
	std::stringstream ss;
	
	std::vector<sf::Drawable *> elements;
	
	void update_step(bool add);
	void update();
};


#endif // SIMULATION_H_INCLUDED
