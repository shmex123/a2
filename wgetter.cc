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
#include "utils.h"

namespace a2 {

DocumentEvent* Wgetter::wget(RequestEvent& r) {
	std::string cmd = "wget ";
	cmd += r.url;
	exec(cmd);
	std::cout << "genterating doc\n";
	std::vector<unsigned char> doc = std::vector<unsigned char>();
	std::string filename = Utils::sharedInstance().filenameFromUrl(r.url);
	std::ifstream t(filename);
	std::string docString((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
	doc.insert(doc.end(), docString.begin(), docString.end());
	return new DocumentEvent(doc);
}

void Wgetter::exec(std::string cmd) {
	/*
	FILE* pipe = popen(cmd.c_str(), "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	std::cout << result << std::endl;
	return result;
	*/
	system(cmd.c_str());
}
}
