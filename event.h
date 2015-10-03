/* -----------------------------------------------------------------------------
 * Event Interface
 * -----------------------------------------------------------------------------
 */

#ifndef EVENT_H
#define EVENT_H

namespace a2 {
class Event {
	public:
	int getType();
	unsigned char* getBytes();
	private:
};
}


#endif
