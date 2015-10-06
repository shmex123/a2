/* -----------------------------------------------------------------------------
 * Reader Header File
 * -----------------------------------------------------------------------------
 */

#ifndef READER_H
#define READER_H

#include "eventHandler.h"

namespace a2 {
class Reader: public EventHandler {
	public:
	void handleEvent(Event& event) override;
};
}


#endif
