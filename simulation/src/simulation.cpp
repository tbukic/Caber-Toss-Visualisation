#include "simulation.h"

#include <iostream>
#include <system_error>
#include <cmath>
#include <algorithm>

#include <iostream>


Record::Record(std::string const & phase, double x, double y, double angle) {
	m_phase = phase;
	m_x = x;
	m_y = y;
	m_angle = angle;
}
std::string Record::get_phase() const {
	return m_phase;
}
double Record::get_x() const {
	return m_x;
}
double Record::get_y() const {
	return m_y;
}
double Record::get_angle() const {
	return m_angle;
}


std::vector<Record> const & SimRecorder::get_records() const {
	return m_recorded;
}
	
SimRecorder::SimRecorder() {
}
void SimRecorder::record_line(std::string const & phase, CaberMotion & caber_motion) {
	m_recorded.push_back(Record(phase, caber_motion.x_coord(), caber_motion.y_coord(), caber_motion.angle()));
}
void SimRecorder::record_attempt(CaberMotion &) {
}
unsigned long SimRecorder::stop_recording() {
	return 0L;
}
unsigned int SimRecorder::buffer_size() {
	return 0;
}
SimRecorder::~SimRecorder() {
}

Scene::~Scene() {
}

const double Simulation::PI = acos(-1.0);

Simulation::Simulation(std::unique_ptr<Configuration> const & config)
	: m_not_closed(true),
	m_window(
		sf::VideoMode(
		config->screen_width(),
		config->screen_heigth()),
		"Simulation"
	),
	m_scale(nullptr),
	m_caber_shape(new CaberShape(0.0, 0.0, config->caber_color())),
	m_caber(nullptr),
	m_caber_motion(nullptr),
	m_toss_model(new EulerTossModel(config->delta_time())),
	m_background(),
	m_font(),
	m_font_loaded(false),
	m_sceneGraph(),
	m_set_mass_title(config->mass_title()),
	m_set_mass_unit(config->mass_unit()),
	m_set_height_title(config->height_title()), 
	m_set_height_unit(config->height_unit()),
	m_set_acc_title(config->acc_title()), 
	m_set_acc_unit(config->acc_unit()),
	m_set_hforce_title(config->hforce_title()), 
	m_set_hforce_unit(config->hforce_unit()),
	m_set_vforce_title(config->vforce_title()), 
	m_set_vforce_unit(config->vforce_unit()),
	m_thrower_height_title(config->thrower_height_title()),
	m_thrower_height_unit(config->thrower_height_unit()),
	m_angle_title(config->angle_title()),
	m_angle_unit(config->angle_unit()),
	m_delta_time(config->delta_time()),
	m_min_mass(config->caber_mass_min()),
	m_max_mass(config->caber_mass_max()),
	m_cur_mass(config->caber_mass_def()),
	m_min_height(config->caber_height_min()),
	m_max_height(config->caber_height_max()),
	m_cur_height(config->caber_height_def()),
	m_min_acc(config->caber_acc_min()),
	m_max_acc(config->caber_acc_max()),
	m_cur_acc(config->caber_acc_def()),
	m_min_hforce(config->caber_hforce_min()),
	m_max_hforce(config->caber_hforce_max()),
	m_cur_hforce(config->caber_hforce_def()),
	m_min_vforce(config->caber_vforce_min()),
	m_max_vforce(config->caber_vforce_max()),
	m_cur_vforce(config->caber_vforce_def()),
	m_thrower_min_height(config->thrower_height_min()),
	m_thrower_max_height(config->thrower_height_max()),
	m_thrower_cur_height(config->thrower_height_def()),
	m_min_angle(config->caber_angle_min()),
	m_max_angle(config->caber_angle_max()),
	m_cur_angle(config->caber_angle_def()),
	m_caber_width_coef(0.2*PI*m_cur_height/m_cur_mass) {
	m_window.setVerticalSyncEnabled(true);
	//std::cout << "Loading background: " << config->background_src() << std::endl;
	if (m_background.loadFromFile(config->background_src())) {
		m_sceneGraph.push_back(
			new BackgroundNode(m_background)
		);
	}
	
	if (m_font.loadFromFile(config->font_path())) {
		m_font_loaded = true;
	}
	m_scale.reset(new ScaleNode(m_window, m_font, config->scale_angle_range()));	
}

void Simulation::run() {
	while (m_not_closed) {		
		set_caber();
		set_toss();
		toss_caber();
	}
}

void Simulation::set_caber() {
	m_sceneGraph.push_back(m_scale.get());
	
	m_cur_height = use_scale(
		m_set_height_title, m_set_height_unit,  m_min_height, m_cur_height, m_max_height
	);
	m_cur_mass = use_scale(
		m_set_mass_title, m_set_mass_unit, m_min_mass, m_cur_mass, m_max_mass
	);
	m_caber.reset(new Caber(m_cur_mass, m_cur_height));
	m_sceneGraph.pop_back();
}

void Simulation::set_toss() {
	m_sceneGraph.push_back(m_scale.get());
	
	m_cur_angle = use_scale(
		m_angle_title, m_angle_unit,  m_min_angle, m_cur_angle, m_max_angle
	);
	
	m_thrower_cur_height = use_scale(
		m_thrower_height_title, m_thrower_height_unit,  m_thrower_min_height, m_thrower_cur_height, m_thrower_max_height
	);
	m_caber_motion.reset(new CaberMotion(0.0, m_thrower_cur_height, m_cur_angle/ScaleNode::TO_DEG_COEF));
	
	m_cur_acc = use_scale(
		m_set_acc_title, m_set_acc_unit,  m_min_acc, m_cur_acc, m_max_acc
	);
	m_toss_model->set_acceleration(m_cur_acc);
	m_cur_hforce = use_scale(
		m_set_hforce_title, m_set_hforce_unit, m_min_hforce, m_cur_hforce, m_max_hforce
	);
	m_toss_model->set_horizontal_force(m_cur_hforce);
	m_cur_vforce = use_scale(
		m_set_vforce_title, m_set_vforce_unit, m_min_vforce, m_cur_vforce, m_max_vforce
	);
	m_toss_model->set_vertical_force(m_cur_vforce);
	m_sceneGraph.pop_back();
}

void Simulation::toss_caber() {
	SimRecorder * rec = new SimRecorder();
	std::unique_ptr<Recorder> recorder(rec);
	m_toss_model->start_recording(recorder, EulerTossModel::TypeOfRecording::everything);
	m_toss_model->evaluate(*m_caber_motion, *m_caber);
	
	std::vector<Record> const & records = rec->get_records();
	
	double hmax = 0, wmax = 0;
	for (auto & rec : records) {
		wmax = std::max(rec.get_x(), wmax);
		hmax = std::max(rec.get_y(), hmax);
	}
	const double start_x = 0.95*m_window.getSize().x, start_y = m_window.getSize().y;
	const double coef = std::min(start_x/(wmax + 2*m_cur_height), start_y/(hmax + 2*m_cur_height));
	m_caber_shape->updateSize(20, coef*m_cur_height);
	m_sceneGraph.push_back(m_caber_shape.get());
	
	sf::Time simulation_length = sf::seconds(m_delta_time*records.size());
	sf::Clock clock;
	sf::Time elapsed;
	int index;
	size_t pos;
	std::stringstream ss;
	std::string s;
	while((elapsed = clock.getElapsedTime()) < simulation_length && m_window.isOpen()) {
		ss.str("");
		ss.clear();
		ss << elapsed.asSeconds()/m_delta_time;
		ss >> s;
		pos = s.find('.');
		pos = pos == std::string::npos ? s.size() : pos;
		index = std::stoi(s.substr(0, pos));
		ss.flush();
		m_caber_shape->setPosition(start_x - coef*records[index].get_x(), start_y - coef*records[index].get_y());
		m_caber_shape->updateAngle(records[index].get_angle()*ScaleNode::TO_DEG_COEF + 180.0);
		render();
		//m_caber_shape->setPosition(start_x/2.0, start_y/2.0);
	}
	
	ProcessEvents p;
	m_sceneGraph.pop_back();
	m_toss_model->stop_recording();
}

double Simulation::use_scale(
	std::string const & title, std::string const & metric_unit,
	double min_value, double def_value, double max_value
) {
	m_scale->set(title, metric_unit, min_value, def_value, max_value);
	auto const process = [&](sf::Event & event) {
		m_scale->process_event(event);
	};
	ProcessEvents event_process;
	event_process.push_back(process);
	while (m_window.isOpen() && !m_scale->is_done()) {
		process_events(event_process);
		render();
	}
	double result = m_scale->get_current_value();
	m_scale->reset_scale();
	return result;
}

void Simulation::process_events(ProcessEvents & process_events) {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
			m_not_closed = false;
		} else {
			for (auto & process : process_events) {
				process(event);
			}
		}
	}
}

void Simulation::render() {
	m_window.clear();
	for (auto & node : m_sceneGraph) {
		m_window.draw(*node);
	}
	m_window.display();
}

void CaberShape::parse_color(std::string & color, int & r, int & g, int & b) {
	std::stringstream ss;
	ss << color;
	try {
		ss >> r >> g >> b;
	} catch (std::system_error & err) {
		r = 83;
		g = 53;
		b = 10;
	}
}

CaberShape::CaberShape(float width, float height, std::string color)
	: shape(/*sf::Vector2f(width, height)*/),
	m_width(width), m_height(height) {
	int r, g, b;
	parse_color(color, r, g, b);
	shape.setFillColor(sf::Color(r, g, b));
	updateAngle(0);
}
void CaberShape::draw(
	sf::RenderTarget & target, 
	sf::RenderStates states
) const {
	states.transform *= getTransform();
	target.draw(shape, states);
	//std::cout << "crtam w:" << m_width << " h:" <<  m_height<< std::endl;
}
	
void CaberShape::process_event(sf::Event &) {
}

void CaberShape::updateAngle(float angle) {
	this->setRotation(270 + angle);
}

void CaberShape::updateSize(float width, float height) {
	m_width = width;
	m_height = height;
	shape.setSize(sf::Vector2f(m_width,m_height));
}

BackgroundNode::BackgroundNode(sf::Texture const & texture)
	: m_picture(texture) {
}
	
void BackgroundNode::process_event(sf::Event &) {
}

void BackgroundNode::draw(
	sf::RenderTarget & target, 
	sf::RenderStates states
) const {
	states.transform *= getTransform();
	target.draw(m_picture, states);
}



const double ScaleNode::RADIUS = 0.3;
const double ScaleNode::BORDER_LINE_LEN = 0.4;
const double ScaleNode::HALF_LINE_LEN = 0.6*BORDER_LINE_LEN;
const double ScaleNode::TICK_LEN = 0.7;
const double ScaleNode::THICK_COEF = 0.05;
const double ScaleNode::UPDATE_COEF = 0.01;
const double ScaleNode::TO_DEG_COEF = 180.0/acos(-1.0);

const sf::Color & ScaleNode::FILL_COLOR = sf::Color::Black;
const sf::Color & ScaleNode::OUTLINE_COLOR = sf::Color::Red;
const sf::Color & ScaleNode::TICK_COLOR = sf::Color(83, 53, 10);


ScaleNode::ScaleNode(
	sf::RenderWindow & window,
	sf::Font & font,
	double angle_range,
	double ratio
): 
	m_not_set(true),
	m_done(false),
	m_mouse_held(false),
	m_window(window),
	m_angle_range(angle_range),
	m_min_value(0.0),
	m_max_value(angle_range/2),
	m_cur_value(angle_range),
	m_ratio(std::min(ratio, 1.0)),
	m_dim(std::min(window.getSize().x, window.getSize().y)),
	m_center_x(window.getSize().x/2.0),
	m_center_y(window.getSize().y*1.0 + 1.0/3.0*normalize(RADIUS)),
	m_title_text("TITLE"),
	m_metric_unit("x"),
	m_title(),
	m_scale_circle(normalize(RADIUS)),
	m_scale_min(sf::Vector2f(
		THICK_COEF*normalize(RADIUS), normalize(BORDER_LINE_LEN) + normalize(RADIUS))
	),
	m_scale_max(
		sf::Vector2f(THICK_COEF*normalize(RADIUS), normalize(BORDER_LINE_LEN) + normalize(RADIUS))
	),
	m_scale_mid(sf::Vector2f(
		THICK_COEF/1.5*normalize(RADIUS), normalize(HALF_LINE_LEN) + normalize(RADIUS))
	),
	m_scale_tick(
		sf::Vector2f(THICK_COEF*normalize(RADIUS), normalize(TICK_LEN) + normalize(RADIUS))
	),
	s(),
	ss(),
	elements{
		&m_title, &m_scale_tick, & m_scale_min,
		&m_scale_max, &m_scale_mid, &m_scale_circle
	} {
	m_title.setFont(font);
	m_title.setColor(sf::Color::Black);
	m_title.setCharacterSize(40);
	
	const double R = normalize(RADIUS);
	
	m_scale_circle.setPosition(m_center_x - R, m_center_y - R);
	m_scale_circle.setOutlineThickness(THICK_COEF*R);
	m_scale_circle.setFillColor(FILL_COLOR);
	m_scale_circle.setOutlineColor(OUTLINE_COLOR);

	const double FULL_ANGLE = 180.0;
	m_scale_min.setRotation(FULL_ANGLE - m_angle_range/2.0);
	m_scale_mid.setRotation(FULL_ANGLE);
	m_scale_max.setRotation(FULL_ANGLE + m_angle_range/2.0);
	
	m_scale_min.setPosition(m_center_x, m_center_y);
	m_scale_mid.setPosition(m_center_x, m_center_y);
	m_scale_max.setPosition(m_center_x, m_center_y);
	m_scale_tick.setPosition(m_center_x, m_center_y);
		

	m_scale_tick.setFillColor(TICK_COLOR);
	m_scale_min.setFillColor(OUTLINE_COLOR);
	m_scale_mid.setFillColor(OUTLINE_COLOR);
	m_scale_max.setFillColor(OUTLINE_COLOR);
	
}
	
double ScaleNode::normalize(double value) {
	return m_ratio*m_dim*value;
}
	
void ScaleNode::set(std::string const & title, std::string const & metric_unit, double min_value, double def_value, double max_value) {
	if (min_value > def_value || def_value > max_value) {
		//throw std:: nešto
	}
	m_min_value = min_value;
	m_max_value = max_value;
	m_cur_value = def_value;
	m_metric_unit = metric_unit;
	m_title_text = title;
	update();
	m_not_set = false;
	m_done = false;
}

void ScaleNode::process_event(sf::Event & event) {
	using kb = sf::Keyboard;
	if (event.type == sf::Event::KeyPressed) {
		const static kb::Key & code = event.key.code;
		const static bool SUB = false, ADD = true;
		if (code == kb::Return || code == kb::Space) {
			m_done = true;
		} else if (
			code == kb::Left ||
			code == kb::Down || 
			code == kb::Subtract
		) {
			update_step(SUB);
		} else if 
			(code == kb::Right ||
			code == kb::Up ||
			code == kb::Add
		) {
			update_step(ADD);
		}
	} /*else if (
		event.type == sf::Event::MouseWheelScrolled &&
		event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel
	) {
		int M = event.mouseWheelScroll.delta;
		bool positive = M > 0;
		M = positive ? M : -M;
		for (int i = 0; i < M; ++i) {
			update_step(positive);
		}
	} */else if (
		event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left
	) {
		sf::Vector2f mouse = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		sf::FloatRect bounds = m_scale_tick.getGlobalBounds();
		m_mouse_held = bounds.contains(mouse);
	} else if (
		m_mouse_held &&
		event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left
	) {
		m_mouse_held = false;
	} else if (
		m_mouse_held &&
		event.type == sf::Event::MouseMoved
	) {
		const double
			x =  sf::Mouse::getPosition(m_window).x,
			y =  sf::Mouse::getPosition(m_window).y,
			dx = (m_center_x - x),
			dy = (m_center_y - y),
			sign = x > m_center_x ? 1 : -1,
			angle = sign*to_deg(acos(dy/std::sqrt(dx*dx + dy*dy))) + m_angle_range/2.0,
			coef = std::min(std::max(angle/m_angle_range, 0.0), 1.0);
			m_cur_value = m_min_value + coef*(m_max_value - m_min_value);
		update();
	}
}
	
void ScaleNode::draw(
	sf::RenderTarget& target, 
	sf::RenderStates states
) const {
	if (m_not_set) {
		return;
	}
	states.transform *= getTransform();
	for (auto & element : elements) {
		target.draw(*element, states);
	}
}

double ScaleNode::to_deg(double rad) {
	return rad*TO_DEG_COEF;
}
	
bool ScaleNode::is_done() const {
	return m_done;
}
	
void ScaleNode::reset_scale(){
	m_not_set = true;
}

double ScaleNode::get_current_value() const {
	if (!m_done) {
		// throw std:: nešto
	}
	return m_cur_value;
}	
void ScaleNode::update_step(bool add) {
	double sign = add ? 1.0 : -1.0;
	double tmp = m_cur_value + (m_max_value - m_min_value)*UPDATE_COEF*sign;
	m_cur_value = std::min(m_max_value, std::max(m_min_value, tmp));
	update();
}
	
void ScaleNode::update() {
	ss.str("");
	ss.precision(5);
	ss << "  " << m_title_text << "  :  " << m_cur_value << " " << m_metric_unit;
	s = ss.str();
	m_title.setString(s);
	const double range = m_max_value - m_min_value;
	const double rot_coef = (range/2.0 - m_cur_value + m_min_value)/range;
	m_scale_tick.setRotation(180.0 - rot_coef*m_angle_range);
}
