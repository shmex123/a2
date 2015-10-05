

#include <iostream>
#include <vector>
#include "netTuple.h"
#include "utils.h"


namespace a2 {
	NetTuple::NetTuple(std::string serverParam, std::string portParam) {
		server = serverParam;
		port = portParam;
		numBytes = 0;
	}

	NetTuple::NetTuple(std::vector<unsigned char> data) {
		std::vector<unsigned char>::const_iterator urllenbegin = data.begin();
		std::vector<unsigned char>::const_iterator urllenend = data.begin() + 4;
		std::vector<unsigned char> urllenbytes(urllenbegin, urllenend);
		int urllen = Utils::sharedInstance().charsToInt(urllenbytes);

		std::vector<unsigned char>::const_iterator urlbegin = data.begin() + 4;
		std::vector<unsigned char>::const_iterator urlend = data.begin() + 4 + urllen;
		std::vector<unsigned char> urlbytes(urlbegin, urlend);
		std::string urlParam(urlbytes.begin(), urlbytes.end());
		server = urlParam;
		
		numBytes = urllen + 8;

		std::vector<unsigned char>::const_iterator portbegin = data.begin() + 4 + urllen;
		std::vector<unsigned char>::const_iterator portend = data.begin() + 4 + urllen + 4;
		std::vector<unsigned char> portbytes(portbegin, portend);
		int portParam = Utils::sharedInstance().charsToInt(portbytes);
		port = std::to_string(portParam);

		std::cout << "Created: " << server << ":" << port << " bytecount: " << numBytes << std::endl;
	}

	std::vector<unsigned char> NetTuple::getBytes() {
		// Wireformat
		// UrlLength: Int
		// Url: String
		// Port: Int
		std::vector<unsigned char> data = std::vector<unsigned char>();
		std::vector<unsigned char> urllenbytes = Utils::sharedInstance().intToChars(server.length());
		data.insert(data.end(), urllenbytes.begin(), urllenbytes.end());
		data.insert(data.end(), server.begin(), server.end());
		std::vector<unsigned char> portbytes = Utils::sharedInstance().intToChars(stoi(port));
		data.insert(data.end(), portbytes.begin(), portbytes.end());
		return data;
	}

	bool NetTuple::operator==(const NetTuple& other) {
		return (server == other.server) && (port == other.port);
	}

	bool NetTuple::operator!=(const NetTuple& other) {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& o, const NetTuple& n) {
		return o << n.server << ", " << n.port;
	}
}
