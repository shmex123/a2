/* -----------------------------------------------------------------------------
 * Error Event Interface
 * -----------------------------------------------------------------------------
 */

#ifndef ERROR_EVENT_H
#define ERROR_EVENT_H

#include <string>
#include <vector>
#include "event.h"
#include "tcpConnection.h"

namespace a2 {
class ErrorEvent: public Event {
	public:
	ErrorEvent(TCPConnection con);
	ErrorEvent(std::string msg);
	friend std::ostream& operator<<(std::ostream& o, const ErrorEvent& r);
	int getType() override;
	std::vector<unsigned char> getBytes() override;
	std::string msg;
	private:
};
}


#endif
