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
#include "wgetter.h"

namespace a2 {

Tunnel::Tunnel(int sockfd) {
	sourceConnection = new TCPConnection(this, sockfd);
	chain = NULL;
}

void Tunnel::handleEvent(Event& event) {
	switch(event.getType()) {
        case REQUEST_EVENT: handleRequestEvent(static_cast<RequestEvent&>(event)); break;
        case CHAIN_EVENT: handleChainEvent(static_cast<Chain&>(event)); break;
        case DOCUMENT_EVENT: handleDocumentEvent(static_cast<DocumentEvent&>(event)); break;
        default: std::cout << "unknown event sent to event handler" << std::endl; break;
        }
}

void Tunnel::handleChainEvent(Chain& c) {
	chain = &c;
	chain->removeFromChain(chain->getTupleFromHostname());
}

void Tunnel::handleRequestEvent(RequestEvent& r) {
	if(chain != NULL) {
		std::cout << *chain << std::endl;
		if(chain->isLastHop()) {
			performWget(r);
		} else {
			forwardRequest(r);
		}
	} else {
		std::cerr << "Received a request event prior to chain!" << std::endl;
	}
}

void Tunnel::handleDocumentEvent(DocumentEvent& d) {
	sourceConnection->sendEvent(d);
}

void Tunnel::performWget(RequestEvent& r) {
	std::cout << "issuing wget for file " << r.url << std::endl;
	std::vector<unsigned char> data = std::vector<unsigned char>();
	DocumentEvent* d = Wgetter::sharedInstance().wget(r);
	sourceConnection->sendEvent(*d);
}

void Tunnel::forwardRequest(RequestEvent& r) {
	NetTuple* tuple = chain->getNextSS();
	std::cout << "next SS is " << *tuple << std::endl;
	destConnection = new TCPConnection(this, tuple->server, tuple->port);
	destConnection->sendEvent(*chain);
	destConnection->sendEvent(r);
}
}
