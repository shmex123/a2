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

void SteppingStone::startServer() {

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
	while(1) {
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
		onClientConnect(new_fd);
	}
}
void SteppingStone::onClientConnect(int new_sock_fd) {
	std::cout << "Client connected." << std::endl;
	tunnels.push_back(Tunnel(new_sock_fd));
}

void SteppingStone::start() {
	startServer();
}

}

int main() {
	a2::SteppingStone ss = a2::SteppingStone("11111");
	ss.start();
}
