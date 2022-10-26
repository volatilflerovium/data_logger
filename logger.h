#ifndef LOGGER_H
#define LOGGER_H

#include "data_logger.h"
#include "ilogger.h"

class Logger : public ILogger
{
	public:
		Logger(const char* filePath, const char* separator = " # ")
		: m_dataLogger(filePath, separator)
		{}
		
		virtual ~Logger()
		{}

		void addData(const char* field, int data) { 
			m_dataLogger.addDataT(std::move(field), data);
		}
		
		void addData(const char* field, const char* data) { 
			m_dataLogger.addDataT(std::move(field), std::move(data));
		}
		
		void addData(const char* field, const std::string& data) { 
			m_dataLogger.addDataT(std::move(field), data);
		}
		
		void addData(const char* field, bool data) { 
			m_dataLogger.addDataT(std::move(field), data);
		}
		
		void addData(const char* field, float data) { 
			m_dataLogger.addDataT(std::move(field), data);
		}
		
		void addData(const char* field, double data) { 
			m_dataLogger.addDataT(std::move(field), data);
		}
		
		void printLine(const char* line){
			m_dataLogger.printLine(std::move(line));
		}
	
		void printHeader(){
			m_dataLogger.printHeader();
		}

		void addHeaderField(const char* fieldName, char align, int width = 0){
			m_dataLogger.addHeaderField(std::move(fieldName), align, width);
		}

		void flushBuffer(){
			m_dataLogger.flushBuffer();
		}

	private:
		DataLogger m_dataLogger;
};



#endif
