/* -----------------------------------------------------------------------------
 * TCPConnection Header File
 * -----------------------------------------------------------------------------
 */

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <vector>
#include <string>
#include <pthread.h>
#include "event.h"
#include "eventHandler.h"

namespace a2 {
class TCPConnection {
	public:
	TCPConnection(EventHandler* handlerP, std::string serverP, std::string portP);
	TCPConnection(EventHandler* handlerP, int sockfdP);
	void sendEvent(Event& event);
	std::vector<unsigned char> receive(int numBytes);
	void join();
	private:
	std::string server;
	std::string port;
	int sockfd;
	pthread_t recv_thread;
	EventHandler* handler;
	static void* startReceive(void* param);
};
}


#endif
