#ifndef ILOGGER_H
#define ILOGGER_H

class ILogger
{
	public:
	
		/*
		 * Add data to the log file on the corresponding column marked by
		 * the header of the same name of its first parameters.
		 * 
		 * @param fieldName name of the corresponding column
		 * @param data the data to be logged under the header fieldName
		 * 
		 * See notes below.
		 **/
		virtual void addData(const char* field, int data)=0;
		virtual void addData(const char* field, const char* data)=0;
		virtual void addData(const char* field, const std::string& data)=0;
		virtual void addData(const char* field, bool data)=0;
		virtual void addData(const char* field, float data)=0;
		virtual void addData(const char* field, double data)=0;

		/*
		 * Print the input as a new line in the log file.
		 * 
		 * @param line const char* to be printed in a new line
		 * */
		virtual void printLine(const char* line)=0;
	
	   /*
	    * Print the headers for the table. This will flush the buffer
	    * to the log file. 
	    * 
	    * */
		virtual void printHeader()=0;

		/*
		 * Add a header to the table log.
		 * 
		 * @param fieldName the name of the header for the specific column
		 * @param align the aligment for the data in that column values:
		 *        'l' for left align, 'c' center, 'r' right
		 * @param with the maximum length for the column if it is 0 then
		 *        it will be the same as the length of the header. 
		 * 
		 * printHeader should be called after the last call to addHeaderField.
		 * 
		 * Note: the headers will be set/printed in the sequence they are
		 * set. They just need to be set once.
		 * */
		virtual void addHeaderField(const char* fieldName, char align, int width = 0)=0;
	
		/*
		 * Explicitly flush the buffer.
		 * 
		 * */
		virtual void flushBuffer()=0;
};

#endif
