/* -----------------------------------------------------------------------------
 * TCPConnection Implementation
 * -----------------------------------------------------------------------------
 */

#include <stdexcept>
#include <vector>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
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
	std::string str(data.begin(), data.end());
	unsigned char* bytes = &data[0];
	send(sockfd, bytes, data.size(), 0);
}

std::vector<unsigned char> TCPConnection::receive(int numBytes) {
	unsigned char buffer[numBytes];
	std::vector<unsigned char> bytevector = std::vector<unsigned char>();
	int numReceived = 0;
	while(numReceived < numBytes) {
		int response = recv(sockfd, buffer, numBytes, 0);
		if(response <= 0) {
			throw std::runtime_error("Socket closed.");
		}
		numReceived += response;
		for(int i = 0; i < response; i++)
			bytevector.push_back(buffer[i]);
	}
	return bytevector;
}

void TCPConnection::join() {
	if(pthread_join(recv_thread, NULL)) {
		std::cout << "Error joining receive thread!" << std::endl;
	}
}

void TCPConnection::close() {
	::close(sockfd);
}

void* TCPConnection::startReceive(void* param) {
	TCPConnection con = *((TCPConnection *)param);
	try {
	while(1) {
		Event* e = EventFactory::sharedInstance().createEvent(con);
		con.handler->handleEvent(*e);
	}
	} catch(const std::runtime_error& e) {
		std::cout << "Connection closed." << std::endl;
	}
	return NULL;
}

}
