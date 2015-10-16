/* -----------------------------------------------------------------------------
 * TCPConnection Implementation
 * -----------------------------------------------------------------------------
 */

#include <vector>
#include <iostream>
#include <netdb.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "tcpConnection.h"
#include "utils.h"
#include "protocol.h"
#include "eventFactory.h"

namespace a2 {

TCPConnection::TCPConnection(EventHandler* h, std::string s, std::string p) {
	handler = h;
	server = s;
	port = p;
	
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(server.c_str(), port.c_str(), &hints, &res);
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        connect(sockfd, res->ai_addr, res->ai_addrlen);
	if(pthread_create(&recv_thread, NULL, startReceive, this)) {
		std::cerr << "Failed to start receive thread!" << std::endl;
	}
}

TCPConnection::TCPConnection(EventHandler* h, int s) {
	handler = h;
	sockfd = s;
	if(pthread_create(&recv_thread, NULL, startReceive, this)) {
		std::cerr << "Failed to start receive thread!" << std::endl;
	}
}

void TCPConnection::sendEvent(Event& event) {
	std::vector<unsigned char> data = event.getBytes();
	unsigned char* bytes = &data[0];
	send(sockfd, bytes, data.size(), 0);
}

std::vector<unsigned char> TCPConnection::receive(int numBytes) {
	unsigned char bytes[numBytes];
	int response = recv(sockfd, bytes, numBytes, 0);
	std::vector<unsigned char> bytevector = std::vector<unsigned char>();
	for(int i = 0; i < numBytes; i++)
		bytevector.push_back(bytes[i]);
	return bytevector;
}

void TCPConnection::join() {
	if(pthread_join(recv_thread, NULL)) {
		std::cout << "Error joining receive thread!" << std::endl;
	}
}

void* TCPConnection::startReceive(void* param) {
	TCPConnection con = *((TCPConnection *)param);
	Event* e = EventFactory::sharedInstance().createEvent(con);
	con.handler->handleEvent(*e);
	return NULL;
}


}
