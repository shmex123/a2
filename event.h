/* -----------------------------------------------------------------------------
 * Event Interface
 * -----------------------------------------------------------------------------
 */

#ifndef EVENT_H
#define EVENT_H

#include <vector>

namespace a2 {
class Event {
	public:
	virtual int getType() = 0;
	virtual std::vector<unsigned char> getBytes() = 0;
	private:
};
}


#endif
