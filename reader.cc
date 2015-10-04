

#include <iostream>
#include <vector>
#include "reader.h"
#include "chainfileParser.h"

using namespace a2;


void Reader::handleEvent(Event event) {
}

int main() {
	ChainfileParser parser = ChainfileParser::sharedInstance();
	Chain c = parser.parse();
	std::cout << c << std::endl;
}
