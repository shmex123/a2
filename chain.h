/* -----------------------------------------------------------------------------
 * Chain Header 
 * -----------------------------------------------------------------------------
 */

#ifndef CHAIN_H
#define CHAIN_H

#include <list>

#include "netTuple.h"
#include "event.h"

namespace a2 {
class Chain: Event {
	public:
	Chain(unsigned char* bytes);
	Chain(std::list<NetTuple> tuples);
	NetTuple* getNextSS();
	bool isLastHop(NetTuple);
	friend std::ostream& operator<<(std::ostream&, const Chain &c);
	private:
	std::list<NetTuple> nodes;
};
}


#endif
