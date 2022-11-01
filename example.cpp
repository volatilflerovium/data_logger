#include <iostream>
#include "logger.h"

// g++ -std=c++17 logger_test.cpp data_logger.cpp -lstdc++fs -o logger


int main(){

	ILogger* logger=new Logger("/tmp/A/data_test", " | ");
	
	logger->addHeaderField("Field 1", 'c');
	logger->addHeaderField("Field 2", 'r');
	logger->addHeaderField("Field 3", 'l', 10);
	logger->printHeaders();
	
	logger->addData("Field 1", 12);
	logger->addData("Field 2", 123);
	logger->addData("Field 3", 1234.56789);
	logger->flushBuffer();
	
	logger->addData("Field 3", 125);
	logger->addData("Field 1", 1234);
	logger->addData("Field 2", 12);
	logger->flushBuffer();

	logger->addData("Field 3", "hello");
	//logger->addData("Field 1", 1234);
	//logger->addData("Field 2", 12);
	logger->flushBuffer();

	delete logger;
	return 0;
}
