/* -----------------------------------------------------------------------------
 * TCPConnection Header File
 * -----------------------------------------------------------------------------
 */

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <vector>
#include <string>
#include "event.h"
#include "eventHandler.h"

namespace a2 {
class TCPConnection {
	public:
	TCPConnection(EventHandler* handlerP, std::string serverP, std::string portP);
	TCPConnection(EventHandler* handlerP, int sockfdP);
	void sendEvent(Event& event);
	std::vector<unsigned char> receive(int numBytes);
	private:
	std::string server;
	std::string port;
	int sockfd;
	EventHandler* handler;
	void onEventReceived(Event& event);
};
}


#endif
