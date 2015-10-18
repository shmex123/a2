/* -----------------------------------------------------------------------------
 * Utils Implementation
 * -----------------------------------------------------------------------------
 */

#include <string>
#include <vector>
#include "utils.h"

namespace a2 {

int Utils::charsToInt(std::vector<unsigned char> chars) {
	return (chars[0] << 24) + (chars[1] << 16) + (chars[2] << 8) + chars[3];
}

std::vector<unsigned char> Utils::intToChars(int val) {
	std::vector<unsigned char> chars(4);
	for(int i = 0; i < 4; i++)
		chars[3-i] = (val >> (i*8));
	return chars;
}

std::string Utils::filenameFromUrl(std::string url) {
	std::size_t found = url.find_last_of("/\\");
	if(found == std::string::npos) {
		return "index.html";
	} else {
		return url.substr(found + 1);
	}
}

}
