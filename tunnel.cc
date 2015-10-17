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
#include "protocol.h"

namespace a2 {

Tunnel::Tunnel(int sockfd) {
	sourceConnection = new TCPConnection(this, sockfd);
}

void Tunnel::handleEvent(Event& event) {
	switch(event.getType()) {
        case REQUEST_EVENT: std::cout << "handle event for request event called" << std:: endl; break;
        case CHAIN_EVENT: std::cout << "handle event for chain event called" << std:: endl; break;
        default: std::cout << "unknown event sent to event handler" << std::endl; break;
        }
}
}
