/* -----------------------------------------------------------------------------
 * Chain Header 
 * -----------------------------------------------------------------------------
 */

#ifndef CHAIN_H
#define CHAIN_H

#include <vector>

#include "netTuple.h"
#include "event.h"

namespace a2 {
class Chain: Event {
public:
	Chain(unsigned char* bytes);
	Chain(std::vector<NetTuple> tuples);
	NetTuple* getNextSS();
	bool isLastHop(NetTuple);
	friend std::ostream& operator<<(std::ostream& o, const Chain& c);
private:
	std::vector<NetTuple> nodes;
};
}


#endif