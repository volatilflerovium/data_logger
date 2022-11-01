/*********************************************************************
* DataLogger class                               				         *
*                                                                    *
* A class to log data in a table-like format example:                * 
* Field 1 | Field 2 | Field 3 | ...                                  *
* dataA1  | dataA2  | dataA3  |...                                   *
* dataB1  | dataB2  | dataB3  |...                                   *
*                                                                    *
* Date:    17-03-2021                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <filesystem>
#include "ilogger.h"
#include "traits.h"

class DataLogger
{
	public:
		/*
		 * Construct
		 * 
		 * @param filePath path to the log file
		 * @param separator string of characters used to separate 
		 *        the different columns in the log file
		 * 
		 **/ 
		DataLogger(const char* filePath, const char* separator = " # ");
		virtual ~DataLogger();

		/*
		 * Explicitly print the input in a new line in the log file.
		 * 
		 * @param line const char* to be printed in a new line
		 * */
		void printLine(const char* line);
	
	   /*
	    * Print the headers for the table. This will flush the buffer
	    * to the log file. 
	    * 
	    * */
		void printHeaders();
		
		/*
		 * Add a header to the table log.
		 * 
		 * @param fieldName the name of the header for the specific column
		 * @param align the aligment for the data in that column values:
		 *        'l' for left align, 'c' center, 'r' right
		 * @param width the maximum number of character width for the column 
		 *        if it is 0 then it will be the same as the width of the header. 
		 * 
		 * printHeader should be called after the last call to addHeaderField.
		 * 
		 * Note: the headers will be set/printed in the sequence they are
		 * set. They just need to be set once.
		 * */
		void addHeaderField(const char* fieldName, char align, int width = 0);
	
		/*
		 * Add an explicit new line.
		 * 
		 * */
		void breakLine();
	
		/*
		 * Explicitly flush the buffer.
		 * 
		 * */
		void flushBuffer();

		template<typename T>
		void addDataT(const char* fieldName, T data);

	private:
		static constexpr int c_mx_separator_size=30;

	private:	
		std::ofstream m_logFile;
		std::vector<char*> m_buffer;
		std::vector<const char*> m_header;
		std::vector<std::pair<int, char>> m_fieldData;
		std::map<const char*, int> m_fieldPosition;
		char m_separator[c_mx_separator_size];
		const int c_mxWidth;

		DataLogger()=delete;
		DataLogger(const DataLogger&)=delete;
		std::string setPath(const char* filePath);
};

//----------------------------------------------------------------------

inline void DataLogger::printLine(const char* line)
{
	m_logFile << line << '\n';
	m_logFile.flush();
}

//----------------------------------------------------------------------

inline void DataLogger::breakLine() 
{
	m_logFile << "\n";
}

//----------------------------------------------------------------------

template<typename T>
void DataLogger::addDataT(const char* fieldName, T data) 
{			
	if(m_fieldPosition.find(fieldName)==m_fieldPosition.end()){
		return;
	}

	std::string str = ToString<T>::toStr(data);

	int p = str.length();
	int pos = m_fieldPosition[fieldName];

	char* tm = m_buffer[pos];
	std::memset(m_buffer[pos], ' ', c_mxWidth);
	m_buffer[pos][m_fieldData[pos].first] = '\0';

	if (m_fieldData[pos].second != 'l' && m_fieldData[pos].first >= p) {
		if (m_fieldData[pos].second == 'r') {
			p = m_fieldData[pos].first - p;
			tm = m_buffer[pos] + p;
		}
		else if (m_fieldData[pos].second == 'c') {
			tm = m_buffer[pos] + (m_fieldData[pos].first - p) / 2;
		}
	}

	int k = m_fieldData[pos].first;
	if (str.length() < m_fieldData[pos].first) {
		k = str.length();
	}

	std::memcpy(tm, str.c_str(), k);
}

/* 
* While adding headers for the columns of the log via DataLogger::addHeaderField
* is sequencially, adding data to the log via DataLogger::addData is not.
* This means that calling DataLogger::addData does not need to follow 
* the same sequence DataLogger::addHeaderField were set. 
* 
* Example:
* 
* addHeaderField("Field1"...);
* addHeaderField("Field2"...);
* addHeaderField("Field3"...);
* printHeader();
* 
* addData("Field1", "l1a");
* addData("Field2", "l1b");
* addData("Field3", "l1c");
* printHeader();
* 
* //first line of data
* addData("Field2", "l2b");
* addData("Field1", "l2a");
* addData("Field3", "l2c");
* flushBuffer();
* 
* //second line of data
* addData("Field3", "l3c");
* addData("Field2", "l3b");
* addData("Field1", "l3a");
* flushBuffer();
* 
* This will output:
* 
* Field 1 # Field 2 # Field 3
* l1a     # l1b     # l1c
* l2a     # l2b     # l2c
* l3a     # l3b     # l3c
* 
* Note: calling DataLogger::addData with the same first parameter (fieldName)
* will just print out the last value with what it was called.
* 
* Any missing field will be output blank
* */

//#####################################################################

#endif
