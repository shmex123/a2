/* -----------------------------------------------------------------------------
 * Document Event
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include "documentEvent.h"
#include "protocol.h"
#include "utils.h"
#include "tcpConnection.h"

namespace a2 {

DocumentEvent::DocumentEvent(TCPConnection con) {
	std::vector<unsigned char> datalenbytes = con.receive(4);
	int datalen = Utils::sharedInstance().charsToInt(datalenbytes);
	
	documentData = con.receive(datalen);
}

DocumentEvent::DocumentEvent(std::vector<unsigned char> data) {
	documentData = data;
}

std::vector<unsigned char> DocumentEvent::getBytes() {
	std::vector<unsigned char> data = std::vector<unsigned char>();
        std::vector<unsigned char> protocolbytes = Utils::sharedInstance().intToChars(getType());
        data.insert(data.end(), protocolbytes.begin(), protocolbytes.end());
        std::vector<unsigned char> datalenbytes = Utils::sharedInstance().intToChars(documentData.size());
	std::string s(documentData.begin(), documentData.end());
        data.insert(data.end(), datalenbytes.begin(), datalenbytes.end());
        data.insert(data.end(), documentData.begin(), documentData.end());
	
        return data;
}

int DocumentEvent::getType() {
	return DOCUMENT_EVENT;
}

void DocumentEvent::writeToFile(std::string filename) {
	std::string val(documentData.begin(), documentData.end());
	Utils::sharedInstance().writeStringToFile(filename, val);
}

std::ostream& operator<<(std::ostream& o, const DocumentEvent& r) {
	std::string docString(r.documentData.begin(), r.documentData.end());
	return o << DOCUMENT_EVENT << " " << docString;
}

}
