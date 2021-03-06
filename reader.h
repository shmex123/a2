/* -----------------------------------------------------------------------------
 * Reader Header File
 * -----------------------------------------------------------------------------
 */

#ifndef READER_H
#define READER_H

#include <string>
#include "eventHandler.h"
#include "documentEvent.h"
#include "errorEvent.h"

namespace a2 {
class Reader: public EventHandler {
	public:
	std::string filename;
	void handleEvent(Event& event) override;
	void handleDocumentEvent(DocumentEvent& doc);
	void handleErrorEvent(ErrorEvent& err);
};
}


#endif
