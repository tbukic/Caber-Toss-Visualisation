#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <memory>

#include "simulation.h"
#include "configure.h"

int main(int argv, char ** args) {
	Configure config;
	if (argv == 2) {
		try {
			config.read(args[1]);
		} catch (std::runtime_error & err) {
			std::cerr << "Error in reading config file: " << args[1] << std::endl;
			std::cerr << err.what() << std::endl;
		}
	}
	Simulation simulation(config.configuration());
	simulation.run();
	return EXIT_SUCCESS;
}
