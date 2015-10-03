/* -----------------------------------------------------------------------------
 * EventHandler Interface
 * -----------------------------------------------------------------------------
 */

#ifndef EVENT_HANDLER_H 
#define EVENT_HANDLER_H

#include "event.h"

namespace a2 {
class EventHandler {
	public:
	virtual void handleEvent(Event event) = 0;
	private:
};
}


#endif
