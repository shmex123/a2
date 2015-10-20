/* -----------------------------------------------------------------------------
 * SteppingStone Implementation
 * -----------------------------------------------------------------------------
 */

#include <vector>
#include <iostream>
#include <unistd.h>
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


	char hn[150];
	hn[149] = '\0';
	gethostname(hn, 149);
	std::string serv(hn);
	std::cout << "SS listening on " << serv << ":" << port << std::endl;

        addr_size = sizeof their_addr;
	while(1) {
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
		onClientConnect(new_fd);
	}
}
void SteppingStone::onClientConnect(int new_sock_fd) {
	std::cout << "Client connected." << std::endl;
	Tunnel t = Tunnel(new_sock_fd);
	tunnels.push_back(t);
}

void SteppingStone::start() {
	startServer();
}

}

int main(int argc, char **argv) {
	std::string port = DEFAULT_SERVER_PORT;
        int opt;
        while((opt = getopt(argc, argv, "p:")) != -1) {
                switch(opt) {
                case 'p':
                        port = optarg;
                        break;
                default:
                        abort();
                }
        }
	a2::SteppingStone ss = a2::SteppingStone(port);
	ss.start();
}
