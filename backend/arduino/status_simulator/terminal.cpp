#include "terminal.h"

Terminal::Terminal(Stream *stream) : stream(stream) {
};

Terminal::~Terminal(){
}

void Terminal::run() {
	if (stream) {
		while (stream->available()) {
			char c = stream->read();
			if (c == '\r' || c == '\n') {
				anaylseLine(buffer);
				buffer = String();
			} else {
				buffer += c;
			}
		}
	}
}

void Terminal::anaylseLine(String &line) {
	if (line.length()) {
		char command = line.charAt(0);
		int param = -1;
		if(line.length()>2){
			//TODO do something better if more argument
			param = line.substring(2).toInt();
		}

		switch(command){
			// home
			case 'h':
				this->ptrHomeCommand();
				break;

			// tare
			case 't':
				this->ptrTareCommand();
				break;

			//move
			case 'm':
				this->ptrMoveCommand(param);
				break;

			//Unknown
			default:
				this->stream->print("Unknown command: ");
				this->stream->println(command);
		}
	}
}

void Terminal::writeStatus(int distMm, int weightGr){
	this->stream->print("s:");
	this->stream->print(distMm);
	this->stream->print(":");
	this->stream->print(weightGr);
	this->stream->println();
}
