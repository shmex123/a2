/* -----------------------------------------------------------------------------
 * ChainfileParser Implementation
 * -----------------------------------------------------------------------------
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include "chainfileParser.h"
#include "chain.h"

namespace a2 {


	Chain ChainfileParser::parse(std::string filename) {
		std::ifstream in(filename);

		int linenum = 0;
		std::vector<NetTuple> tuples = std::vector<NetTuple>();
		while(!in.eof()) {
			linenum++;
			std::string line;
			std::getline(in, line);

			if(linenum <= 1) {
				//int count = std::stoi(line);
				continue;
			}
			
			std::string delimiter = ", ";
			std::string server = line.substr(0, line.find(delimiter));
			std::string port = line.substr(line.find(delimiter), line.length() - 1);
			
			tuples.push_back(NetTuple(server, port));
		}

		return Chain(tuples);
	}

	Chain ChainfileParser::parse() {
		return parse("chaingang.txt");
	}
}

