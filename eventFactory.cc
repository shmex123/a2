/* -----------------------------------------------------------------------------
 * EventFactory Implementation
 * -----------------------------------------------------------------------------
 */

#include <vector>
#include "event.h"
#include "eventFactory.h"
#include "tcpConnection.h"
#include "protocol.h"
#include "requestEvent.h"
#include "chain.h"
#include "utils.h"

namespace a2 {
Event* EventFactory::createEvent(TCPConnection con) {
	std::vector<unsigned char> typebytes = con.receive(4);
	int type = Utils::sharedInstance().charsToInt(typebytes);
	
	switch(type) {
	case REQUEST_EVENT: return new RequestEvent(con);
	case CHAIN_EVENT: return new Chain(con);
	}
}
}
