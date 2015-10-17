/* -----------------------------------------------------------------------------
 * SteppingStone Header File
 * -----------------------------------------------------------------------------
 */

#ifndef STEPPING_STONE_H
#define STEPPING_STONE_H

#include <vector>
#include <string>
#include "tunnel.h"

namespace a2 {
class SteppingStone {
	public:
	SteppingStone(std::string port);
	void start();
	private:
	std::string port;
	int serversockfd;
	std::vector<Tunnel> tunnels;
	void onClientConnect(int sockfd);
	void startServer();
};
}


#endif
