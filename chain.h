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
	Chain(std::vector<unsigned char> bytes);
	Chain(std::vector<NetTuple> tuples);
	NetTuple* getNextSS();
	bool isLastHop(NetTuple);
	friend std::ostream& operator<<(std::ostream& o, const Chain& c);
	int getType() override;
	std::vector<unsigned char> getBytes() override;
private:
	std::vector<NetTuple> nodes;
};
}


#endif
