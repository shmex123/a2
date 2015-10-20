/* -----------------------------------------------------------------------------
 * Wgetter Implementation 
 * -----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>
#include "wgetter.h"
#include "requestEvent.h"
#include "documentEvent.h"
#include "errorEvent.h"
#include "utils.h"

namespace a2 {

Event* Wgetter::wget(RequestEvent& r) {
	std::string cmd = "wget ";
	cmd += r.url;
	exec(cmd);
	std::vector<unsigned char> doc = std::vector<unsigned char>();
	std::string filename = Utils::sharedInstance().filenameFromUrl(r.url);
	std::ifstream t(filename);
	if(t) {
		std::string docString((std::istreambuf_iterator<char>(t)),
					std::istreambuf_iterator<char>());
		doc.insert(doc.end(), docString.begin(), docString.end());
		std::string rmcmd = "rm ";
		rmcmd += filename;
		exec(rmcmd);
		return new DocumentEvent(doc);
	} else {
		std::string errstr = "Could not retrieve resource: ";
		errstr += r.url;
		return new ErrorEvent(errstr);
	}
}

void Wgetter::exec(std::string cmd) {
	cmd += " 2&> /dev/null";
	FILE* pipe = popen(cmd.c_str(), "r");
	//if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
}
}
