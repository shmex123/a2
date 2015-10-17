/* -----------------------------------------------------------------------------
 * Tunnel Implementation
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <string>
#include "tunnel.h"
#include "tcpConnection.h"
#include "eventHandler.h"
#include "event.h"
#include "requestEvent.h"
#include "documentEvent.h"
#include "protocol.h"

namespace a2 {

Tunnel::Tunnel(int sockfd) {
	sourceConnection = new TCPConnection(this, sockfd);
	chain = NULL;
}

void Tunnel::handleEvent(Event& event) {
	switch(event.getType()) {
        case REQUEST_EVENT: handleRequestEvent(static_cast<RequestEvent&>(event)); break;
        case CHAIN_EVENT: handleChainEvent(static_cast<Chain&>(event)); break;
        default: std::cout << "unknown event sent to event handler" << std::endl; break;
        }
}

void Tunnel::handleChainEvent(Chain& c) {
	chain = &c;
}

void Tunnel::handleRequestEvent(RequestEvent& r) {
	if(chain != NULL) {
		NetTuple* tuple = chain->getTupleFromHostname();
		if(tuple == NULL) {
			std::cerr << "Could not find current stepping stone in chain!" << std::endl;
			return;
		}

		if(chain->isLastHop(*tuple)) {
			performWget(r);
		} else {
			forwardRequest(r);
		}
	} else {
		std::cerr << "Received a request event prior to chain!" << std::endl;
	}
}

void Tunnel::performWget(RequestEvent& r) {
	std::cout << "Performing wget...\n";
	std::vector<unsigned char> data = std::vector<unsigned char>();
	std::string str = "This is test document data.";
	data.insert(data.end(), str.begin(), str.end());
	DocumentEvent d = DocumentEvent(data);
	sourceConnection->sendEvent(d);
}

void Tunnel::forwardRequest(RequestEvent& r) {
	std::cout << "Performing forward...\n";
}
}
