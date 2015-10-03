

#include <iostream>
#include <list>

#include "reader.h"
#include "netTuple.h"
#include "chain.h"


void a2::Reader::handleEvent(a2::Event event) {
}

int main() {
	a2::NetTuple tuple = a2::NetTuple("localhost", "10865");
	std::list<a2::NetTuple> tupleList = std::list<a2::NetTuple>();
	tupleList.push_back(tuple);
	a2::Chain chain = a2::Chain(tupleList);
	std::cout << chain << std::endl;
}
