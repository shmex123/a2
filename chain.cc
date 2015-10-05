

#include <iostream>
#include <vector>
#include "chain.h"
#include "protocol.h"


namespace a2 {
	Chain::Chain(unsigned char* bytes) {
	}

	Chain::Chain(std::vector<NetTuple> tuples) {
		nodes = tuples;
	}

	NetTuple* Chain::getNextSS() {
		return NULL;
	}

	bool Chain::isLastHop(NetTuple tuple) {
		return false;
	}

	std::ostream& operator<<(std::ostream& o, const Chain& c) {
		o << "chainlist is: " << std::endl;
		for(NetTuple tuple : c.nodes) {
			o << tuple;
			if(tuple != c.nodes.back())
				o << std::endl;
		}
		return o;
	}

	int Chain::getType() {
		return CHAIN_EVENT;
	}

	std::vector<unsigned char> Chain::getBytes() {
		return std::vector<unsigned char>();
	}
}
