/* -----------------------------------------------------------------------------
 * Utils Interface
 * -----------------------------------------------------------------------------
 */

#ifndef UTILS_H 
#define UTILS_H

#include <vector>

namespace a2 {
class Utils {
	public:
	static Utils& sharedInstance() {
		static Utils instance;
		return instance;
	}
	int charsToInt(std::vector<unsigned char> chars);
	std::vector<unsigned char> intToChars(int val);
	private:
	Utils(){};
};
}


#endif
