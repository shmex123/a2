

#include <iostream>
#include <vector>
#include "chain.h"


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
		for(NetTuple tuple : c.nodes) {
			o << tuple;
			if(tuple != c.nodes.back())
				o << ", ";
		}
		return o;
	}
}
