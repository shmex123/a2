/* -----------------------------------------------------------------------------
 * Reader Header File
 * -----------------------------------------------------------------------------
 */

#ifndef READER_H
#define READER_H

#include "eventHandler.h"
#include "documentEvent.h"

namespace a2 {
class Reader: public EventHandler {
	public:
	void handleEvent(Event& event) override;
	void handleDocumentEvent(DocumentEvent& doc);
};
}


#endif
