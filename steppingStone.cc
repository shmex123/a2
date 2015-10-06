/* -----------------------------------------------------------------------------
 * SteppingStone Implementation
 * -----------------------------------------------------------------------------
 */

#include <vector>
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "steppingStone.h"
#include "protocol.h"
#include "utils.h"
#include "requestEvent.h"

namespace a2 {

SteppingStone::SteppingStone(std::string p) {
	port = p;
}

void SteppingStone::start() {

	/*
        struct addrinfo hints, *res;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        getaddrinfo(NULL, port.c_str(), &hints, &res);

        serversockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        bind(serversockfd, res->ai_addr, res->ai_addrlen);

        listen(serversockfd, SERVER_BACKLOG);
	std::cout << "Waiting for a connection on localhost port " << port << std::endl;

	struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof their_addr;
        int sockfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
	std::cout << "sockfd: " << sockfd << std::endl;

	unsigned char bytes[4];
	recv(sockfd, bytes, 4, 0);
	*/

	struct sockaddr_storage their_addr;
        socklen_t addr_size;
        struct addrinfo hints, *res;
        int sockfd, new_fd;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        getaddrinfo(NULL, port.c_str(), &hints, &res);

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        bind(sockfd, res->ai_addr, res->ai_addrlen);
        listen(sockfd, SERVER_BACKLOG);


        printf("Waiting for a connection on localhost port %s\n", port.c_str());

        addr_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);


	unsigned char bytes[1024];
	
	recv(new_fd, bytes, 1024, 0);
	std::vector<unsigned char> typebytes = std::vector<unsigned char>();
	for(int i = 0; i < 1024; i++) {
		typebytes.push_back(bytes[i]);
	}
	/*
	int type = Utils::sharedInstance().charsToInt(typebytes);
	std::cout << "Type: " << type << std::endl;
	*/
	RequestEvent r = RequestEvent(typebytes);
	std::cout << r << std::endl;
	
	
	send(new_fd, &typebytes[0], typebytes.size(), 0);
}

}

int main() {
	a2::SteppingStone ss = a2::SteppingStone("11111");
	ss.start();
}
