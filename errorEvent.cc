/* -----------------------------------------------------------------------------
 * Error Event Implementation
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include "errorEvent.h"
#include "protocol.h"
#include "utils.h"
#include "tcpConnection.h"

namespace a2 {

ErrorEvent::ErrorEvent(std::string msgParam) {
	msg = msgParam;
}

ErrorEvent::ErrorEvent(TCPConnection con) {
	std::vector<unsigned char> msglenbytes = con.receive(4);
	int msglen = Utils::sharedInstance().charsToInt(msglenbytes);
	
	std::vector<unsigned char> msgbytes = con.receive(msglen);
	std::string msgParam(msgbytes.begin(), msgbytes.end());
	msg = msgParam;
}

std::vector<unsigned char> ErrorEvent::getBytes() {
	std::vector<unsigned char> data = std::vector<unsigned char>();
	std::vector<unsigned char> protocolbytes = Utils::sharedInstance().intToChars(getType());
	data.insert(data.end(), protocolbytes.begin(), protocolbytes.end());
	std::vector<unsigned char> msglengthbytes = Utils::sharedInstance().intToChars(msg.length());
	data.insert(data.end(), msglengthbytes.begin(), msglengthbytes.end());
	data.insert(data.end(), msg.begin(), msg.end());
	return data;
}

int ErrorEvent::getType() {
	return ERROR_EVENT;
}

std::ostream& operator<<(std::ostream& o, const ErrorEvent& e) {
	return o << ERROR_EVENT << " " << e.msg;
}

}
