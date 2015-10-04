/* -----------------------------------------------------------------------------
 * ChainfileParser Header 
 * -----------------------------------------------------------------------------
 */

#ifndef CHAINFILE_PARSER_H
#define CHAINFILE_PARSER_H

#include <string>
#include "netTuple.h"
#include "event.h"
#include "chain.h"

namespace a2 {
class ChainfileParser {
public:
	static ChainfileParser& sharedInstance() {
		static ChainfileParser instance;
		return instance;
	}
	Chain parse(std::string filename);
	Chain parse();
private:
	ChainfileParser(){};
	//ChainfileParser(ChainfileParser const&);
	//void operator=(ChainfileParser const&);
};
}


#endif
