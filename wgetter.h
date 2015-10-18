/* -----------------------------------------------------------------------------
 * Wgetter Header 
 * -----------------------------------------------------------------------------
 */

#ifndef WGETTER_H
#define WGETTER_H

#include <string>
#include "requestEvent.h"
#include "documentEvent.h"

namespace a2 {
class Wgetter {
public:
	static Wgetter& sharedInstance() {
                static Wgetter instance;
                return instance;
        }
	DocumentEvent* wget(RequestEvent& r);
private:
	Wgetter(){};
	void exec(std::string cmd);
};
}


#endif
