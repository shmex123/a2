/* -----------------------------------------------------------------------------
 * Chain Header 
 * -----------------------------------------------------------------------------
 */

#ifndef CHAIN_H
#define CHAIN_H

#include <vector>

#include "netTuple.h"
#include "event.h"
#include "tcpConnection.h"

namespace a2 {
class Chain: public Event {
public:
	Chain(TCPConnection con);
	Chain(std::vector<unsigned char> bytes);
	Chain(std::vector<NetTuple> tuples);
	NetTuple* getNextSS();
	bool isLastHop();
	void removeFromChain(NetTuple* tuple);
	friend std::ostream& operator<<(std::ostream& o, const Chain& c);
	int getType() override;
	std::vector<unsigned char> getBytes() override;
	NetTuple* getTupleFromHostname();
private:
	std::vector<NetTuple> nodes;
};
}


#endif
