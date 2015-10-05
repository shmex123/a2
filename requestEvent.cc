/* -----------------------------------------------------------------------------
 * Request Event
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include "requestEvent.h"
#include "protocol.h"
#include "utils.h"

namespace a2 {

RequestEvent::RequestEvent(std::string urlParam) {
	url = urlParam;
}

RequestEvent::RequestEvent(std::vector<unsigned char> data) {
	std::vector<unsigned char>::const_iterator first = data.begin();
	std::vector<unsigned char>::const_iterator last = data.begin() + 4;
	std::vector<unsigned char> typeBytes(first, last);
	int type = Utils::sharedInstance().charsToInt(typeBytes);
	if(type != REQUEST_EVENT) {
		std::cerr << "REQUEST EVENT CONSTRUCTOR RECEIVED INCORRECT EVENT TYPE!" << std::endl;
	}

	std::vector<unsigned char>::const_iterator urllenfirst = data.begin() + 4;
	std::vector<unsigned char>::const_iterator urllenlast = data.begin() + 8;
	std::vector<unsigned char> urllenbytes(urllenfirst, urllenlast);
	int urllen = Utils::sharedInstance().charsToInt(urllenbytes);

	std::vector<unsigned char>::const_iterator urlfirst = data.begin() + 8;
	std::vector<unsigned char>::const_iterator urllast = data.begin() + 8 + urllen;
	std::vector<unsigned char> urlbytes(urlfirst, urllast);
	std::string urlParam(urlbytes.begin(), urlbytes.end());
	url = urlParam;
}

std::vector<unsigned char> RequestEvent::getBytes() {
	std::vector<unsigned char> data = std::vector<unsigned char>();
	std::vector<unsigned char> protocolbytes = Utils::sharedInstance().intToChars(getType());
	data.insert(data.end(), protocolbytes.begin(), protocolbytes.end());
	std::vector<unsigned char> urllengthbytes = Utils::sharedInstance().intToChars(url.length());
	data.insert(data.end(), urllengthbytes.begin(), urllengthbytes.end());
	data.insert(data.end(), url.begin(), url.end());
	return data;
}

int RequestEvent::getType() {
	return REQUEST_EVENT;
}

std::ostream& operator<<(std::ostream& o, const RequestEvent& r) {
	return o << REQUEST_EVENT << " " << r.url;
}

}
