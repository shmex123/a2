

#include <iostream>
#include <vector>
#include "chain.h"
#include "protocol.h"
#include "utils.h"


namespace a2 {
	Chain::Chain(std::vector<unsigned char> data) {
		std::vector<unsigned char>::const_iterator typebegin = data.begin();
		std::vector<unsigned char>::const_iterator typeend = data.begin() + 4;
		std::vector<unsigned char> typebytes(typebegin, typeend);
		int type = Utils::sharedInstance().charsToInt(typebytes);
		if(type != CHAIN_EVENT) {
			std::cerr << "INVALID EVENT TYPE IN CHAIN CONSTRUCTOR!" << std::endl;
		}
		
		std::vector<unsigned char>::const_iterator nodecountbegin = data.begin() + 4;
		std::vector<unsigned char>::const_iterator nodecountend = data.begin() + 8;
		std::vector<unsigned char> nodecountbytes(nodecountbegin, nodecountend);
		int nodecount = Utils::sharedInstance().charsToInt(nodecountbytes);
		
		nodes = std::vector<NetTuple>();
		int ptroffset = 0;
		for(int i = 0; i < nodecount; i++) {
			std::vector<unsigned char>::const_iterator nodebegin = data.begin() + 8 + ptroffset;
			std::vector<unsigned char>::const_iterator nodeend = data.end();
			std::vector<unsigned char> nodebytes(nodebegin, nodeend);
			NetTuple tuple = NetTuple(nodebytes);
			ptroffset += tuple.numBytes;
			nodes.push_back(tuple);
		}
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
		// Wireformat
		// Type: Int
		// NodeCount: Int
		// [ UrlLength: Int
		//   Url: String
		//   Port: Int ]

		std::vector<unsigned char> data = std::vector<unsigned char>();
		std::vector<unsigned char> protocolbytes = Utils::sharedInstance().intToChars(getType());
		data.insert(data.end(), protocolbytes.begin(), protocolbytes.end());
		std::vector<unsigned char> nodecountbytes = Utils::sharedInstance().intToChars(nodes.size());
		data.insert(data.end(), nodecountbytes.begin(), nodecountbytes.end());
		for(NetTuple tuple : nodes) {
			std::vector<unsigned char> nodebytes = tuple.getBytes();
			data.insert(data.end(), nodebytes.begin(), nodebytes.end());
		}
		return data;
	}
}
