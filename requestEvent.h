/* -----------------------------------------------------------------------------
 * Request Event Interface
 * -----------------------------------------------------------------------------
 */

#ifndef REQUEST_EVENT_H
#define REQUEST_EVENT_H

#include <string>
#include <vector>
#include "event.h"
#include "tcpConnection.h"

namespace a2 {
class RequestEvent: public Event {
	public:
	RequestEvent(TCPConnection con);
	RequestEvent(std::string url);
	RequestEvent(std::vector<unsigned char> data);
	friend std::ostream& operator<<(std::ostream& o, const RequestEvent& r);
	int getType() override;
	std::vector<unsigned char> getBytes() override;
	std::string url;
	private:
};
}


#endif
