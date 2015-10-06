/* -----------------------------------------------------------------------------
 * SteppingStone Header File
 * -----------------------------------------------------------------------------
 */

#ifndef STEPPING_STONE_H
#define STEPPING_STONE_H

#include <vector>
#include <string>

namespace a2 {
class SteppingStone {
	public:
	SteppingStone(std::string port);
	void start();
	private:
	std::string port;
	int serversockfd;
};
}


#endif
