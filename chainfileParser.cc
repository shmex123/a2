/* -----------------------------------------------------------------------------
 * ChainfileParser Implementation
 * -----------------------------------------------------------------------------
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "chainfileParser.h"
#include "chain.h"
#include "protocol.h"

namespace a2 {


	Chain ChainfileParser::parse(std::string filename) {
		if(filename.empty()) filename = DEFAULT_CHAIN_FILENAME;
		std::ifstream in(filename);

		int linenum = 0;
		int readcount = 1;
		std::vector<NetTuple> tuples = std::vector<NetTuple>();
		while(!in.eof() && linenum <= readcount) {
			std::string line;
			std::getline(in, line);

			if(++linenum <= 1) {
				readcount = std::stoi(line);
				continue;
			}

			
			std::string delimiter = ", ";
			std::string server = line.substr(0, line.find(delimiter));
			std::string port = line.substr(line.find(delimiter) + 1, line.length() - 1);
			server.erase(std::remove_if(server.begin(), server.end(), isspace), server.end());
			port.erase(std::remove_if(port.begin(), port.end(), isspace), port.end());
			
			tuples.push_back(NetTuple(server, port));
		}

		return Chain(tuples);
	}

	Chain ChainfileParser::parse() {
		return parse(DEFAULT_CHAIN_FILENAME);
	}
}

