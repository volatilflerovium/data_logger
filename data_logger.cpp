#include "data_logger.h"

//----------------------------------------------------------------------

DataLogger::DataLogger(const char* filePath, const char* separator)
	:m_logFile(setPath(filePath), std::ios::app),
	c_mxWidth(100)
{
	if(!m_logFile.is_open()){
		throw "Fail to open log file";
	}
	int k = sizeof(separator);
	if (k>=c_mx_separator_size){
		k=c_mx_separator_size-1;
	}
	m_separator[k] = '\0';

	std::memcpy(m_separator, std::move(separator), k);
}

//----------------------------------------------------------------------
	
DataLogger::~DataLogger() {
	m_logFile.close();
	for (int i = 0; i < m_buffer.size(); i++) {
		delete[] m_buffer[i];
	}
}

//----------------------------------------------------------------------

void DataLogger::flushBuffer() {
	char tmp[100];
	for (int i = 0; i < m_fieldData.size(); i++) {
		if (strlen(m_buffer[i]) != 0) {
			m_logFile << m_buffer[i];
			m_buffer[i][0] = '\0';
		}
		else {
			memset(tmp, ' ', c_mxWidth);
			tmp[m_fieldData[i].first] = '\0';
			m_logFile << tmp;
		}
		m_logFile << m_separator;
	}

	m_logFile << '\n';
	m_logFile.flush();
}

//----------------------------------------------------------------------
	
void DataLogger::printHeaders() {
	for (int i = 0; i < m_header.size(); i++) {
		addDataT(m_header[i], m_header[i]);
	}
	flushBuffer();
}

//----------------------------------------------------------------------
	
void DataLogger::addHeaderField(const char* fieldName, char align, int width) {
	std::string str(fieldName);
	m_fieldPosition[fieldName] = m_header.size();
	m_header.emplace_back(std::move(fieldName));
	int w = width;
	if (width == 0 || width < str.length()) {
		w = str.length();
	}
	if (w > c_mxWidth) {
		w = c_mxWidth;
	}
	m_fieldData.emplace_back(w, align);

	char* tmp = new char[c_mxWidth + 1];
	tmp[0] = '\0';
	m_buffer.push_back(tmp);
}

//----------------------------------------------------------------------

std::string DataLogger::setPath(const char* filePath) {
	char buffer[254];
	int t=strlen(filePath);
	std::memcpy(buffer, filePath, t*sizeof(char));
	buffer[t]='\0';
	char pos='/';
	char* ptr = strrchr(buffer, pos); 
	if(ptr){
		int r=ptr-buffer+1;
		char path[r];
		std::memcpy(path, buffer, r-1);
		path[r-1]='\0';
		//mkdir(path, 0777);
		std::filesystem::create_directory(std::filesystem::path{path});//, 0777);
	}
	return filePath;
}

//----------------------------------------------------------------------
