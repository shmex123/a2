/* -----------------------------------------------------------------------------
 * EventFactory Header 
 * -----------------------------------------------------------------------------
 */

#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H

#include <vector>
#include "event.h"
#include "tcpConnection.h"

namespace a2 {
class EventFactory {
public:
	static EventFactory& sharedInstance() {
		static EventFactory instance;
		return instance;
	}
	Event* createEvent(TCPConnection con);
private:
	EventFactory(){};
};
}


#endif
