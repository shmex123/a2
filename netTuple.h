/* -----------------------------------------------------------------------------
 * NetTuple Header
 * -----------------------------------------------------------------------------
 */

#ifndef NET_TUPLE_H
#define NET_TUPLE_H

#include <iostream>


namespace a2 {
class NetTuple {
	public:
	NetTuple(std::string serverParam, std::string portParam);
	std::string server;
	std::string port;
	private:
};
}


#endif
