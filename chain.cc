

#include <iostream>
#include <list>

#include "chain.h"


a2::Chain::Chain(unsigned char* bytes) {
}

a2::Chain::Chain(std::list<NetTuple> tuples) {
	nodes = tuples;
}

a2::NetTuple* a2::Chain::getNextSS() {
	return NULL;
}

bool a2::Chain::isLastHop(a2::NetTuple tuple) {
	return false;
}

std::ostream & operator<<(std::ostream & Str, const a2::Chain & v) {
	/*
	for(a2::NetTuple tuple : v.nodes) {
		Str << tuple.server << ":" << tuple.port << " ";
	}
	*/
	Str << "testing";
	return Str;
}

