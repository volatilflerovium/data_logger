#ifndef LOGGER_H
#define LOGGER_H

#include "data_logger.h"
#include "ilogger.h"

class Logger : public DataLogger
{
	public:
		Logger(const char* filePath, const char* separator = " # ")
		: DataLogger(filePath, separator)
		{}

		void addData(const char* field, int data) { 
			addDataT(std::move(field), data);
		}
		void addData(const char* field, const char* data) { 
			addDataT(std::move(field), std::move(data));
		}
		void addData(const char* field, const std::string& data) { 
			addDataT(std::move(field), data);
		}
		void addData(const char* field, bool data) { 
			addDataT(std::move(field), data);
		}
		void addData(const char* field, float data) { 
			addDataT(std::move(field), data);
		}
		void addData(const char* field, double data) { 
			addDataT(std::move(field), data);
		}
};



#endif
