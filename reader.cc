

#include <iostream>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include "reader.h"
#include "chainfileParser.h"

using namespace a2;


void printUsage() {
	std::cerr << "Usage: ./awget <URL> [-c chainfile]" << std::endl;
	exit(1);
}

void Reader::handleEvent(Event event) {
}

int main(int argc, char** argv) {
	if(argc < 2) {
		printUsage();
	}

	std::string url;
	int opt;
        while((opt = getopt(argc, argv, "c:")) != -1) {
                switch(opt) {
                case 'c':
                        url = optarg;
                        break;
                default:
                        abort();
                }
        }

	try {
		Chain c = NULL;
		if(url.empty()) {
			c = ChainfileParser::sharedInstance().parse();
		} else {
			c = ChainfileParser::sharedInstance().parse(url);
		}
		std::cout << c << std::endl;
	} catch(const std::invalid_argument& ia) {
		std::cerr << "Could not find file ";
		if(url.empty()) {
			std::cerr << "'chaingang.txt'";
		} else {
			std::cerr << "'" << url << "'";
		}
		std::cerr << "!" << std::endl;
		printUsage();
	}
}
