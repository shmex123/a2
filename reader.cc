

#include <iostream>
#include <vector>
#include <stdexcept>
#include <unistd.h>
#include "reader.h"
#include "chainfileParser.h"
#include "requestEvent.h"
#include "documentEvent.h"
#include "protocol.h"
#include "tcpConnection.h"
#include "utils.h"


using namespace a2;

void Reader::handleEvent(Event& event) {
	switch(event.getType()) {
	case REQUEST_EVENT: std::cout << "handle event for request event called" << std:: endl; break;
	case CHAIN_EVENT: std::cout << "handle event for chain event called" << std:: endl; break;
	case DOCUMENT_EVENT: handleDocumentEvent(static_cast<DocumentEvent&>(event)); break;
	default: std::cout << "unknown event sent to event handler" << std::endl; break;
	}
}

void Reader::handleDocumentEvent(DocumentEvent& doc) {
	std::cout << doc << std::endl;
}


void printUsage() {
	std::cerr << "Usage: ./awget <URL> [-c chainfile]" << std::endl;
	exit(1);
}

int main(int argc, char** argv) {
	if(argc < 2) {
		printUsage();
	}
	std::string url = argv[1];
	if(url == "-c") printUsage();

	std::string filename;
	int opt;
        while((opt = getopt(argc, argv, "c:")) != -1) {
                switch(opt) {
                case 'c':
                        filename = optarg;
                        break;
                default:
                        abort();
                }
        }

	Reader reader = Reader();

	try {
		Chain c = ChainfileParser::sharedInstance().parse(filename);
		RequestEvent r = RequestEvent(url);
		std::cout << "Request: " << url << std::endl;
		std::cout << c << std::endl;
		NetTuple* tuple = c.getNextSS();
		TCPConnection con = TCPConnection(&reader, tuple->server, tuple->port);
		con.sendEvent(c);
		con.sendEvent(r);
		std::cout << "Sent request event!" << std::endl;
		con.join();
		//std::vector<unsigned char> typebytes = con.receive(4);
		//int type = Utils::sharedInstance().charsToInt(typebytes);
		//std::cout << "Type: " << type << std::endl;
	} catch(const std::invalid_argument& ia) {
		std::cerr << "Error with file ";
		if(filename.empty()) {
			std::cerr << "'" << DEFAULT_CHAIN_FILENAME << "'";
		} else {
			std::cerr << "'" << filename << "'";
		}
		std::cerr << "!";
		std::cerr << " Does the file exist?" << std::endl;
		printUsage();
	}
}
