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
	bool operator==(const NetTuple& other);
	bool operator!=(const NetTuple& other);
	friend std::ostream& operator<<(std::ostream& o, const NetTuple& n);
	private:
};
}


#endif
