/* -----------------------------------------------------------------------------
 * Tunnel Header File
 * -----------------------------------------------------------------------------
 */

#ifndef TUNNEL_H 
#define TUNNEL_H

#include <vector>
#include <string>
#include "tcpConnection.h"
#include "chain.h"
#include "eventHandler.h"
#include "event.h"

namespace a2 {
class Tunnel : public EventHandler {
	public:
	Tunnel(int sockfd);
	void handleEvent(Event& event);
	private:
	TCPConnection* sourceConnection;
	Chain* chain;
	
};
}


#endif
