

#include <iostream>

#include "netTuple.h"


namespace a2 {
	NetTuple::NetTuple(std::string serverParam, std::string portParam) {
		server = serverParam;
		port = portParam;
	}

	bool NetTuple::operator==(const NetTuple& other) {
		return (server == other.server) && (port == other.port);
	}

	bool NetTuple::operator!=(const NetTuple& other) {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& o, const NetTuple& n) {
		return o << n.server << ":" << n.port;
	}
}
