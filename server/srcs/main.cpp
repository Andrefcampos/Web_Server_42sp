#include "Webserv/Webserv.hpp"

using namespace Webserv;

int	main(void) {
	try {
		parser();
		initEventLoop();
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}