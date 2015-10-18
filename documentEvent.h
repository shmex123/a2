/* -----------------------------------------------------------------------------
 * Document Event Interface
 * -----------------------------------------------------------------------------
 */

#ifndef DOCUMENT_EVENT_H
#define DOCUMENT_EVENT_H

#include <string>
#include <vector>
#include "event.h"
#include "tcpConnection.h"

namespace a2 {
class DocumentEvent: public Event {
	public:
	DocumentEvent(TCPConnection con);
	DocumentEvent(std::vector<unsigned char> d);
	friend std::ostream& operator<<(std::ostream& o, const DocumentEvent& data);
	int getType() override;
	std::vector<unsigned char> getBytes() override;
	void writeToFile(std::string filename);
	private:
	std::vector<unsigned char> documentData;
};
}


#endif
