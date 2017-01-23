#ifndef DATA_H
#define DATA_H

const int ERR_FILE_NOT_FOUND = -1;
const int ERR_NULLPTR = -2;

enum Endian
{
	littleEndian=0,
	bigEndian=1
};

class Data
{
	private:
		Endian endianMode;
		FILE * file;
		unsigned char * buffer;
		long fileLength;
		long getFileLength();
		bool fileLoaded;
	
	public:
		
		Data(Endian Endianness);
		Data(Endian Endianness, const char * filePath);
		void setEndianness(bool e);
		bool isLittleEndian();
		bool isBigEndian();
	
		bool createNewFile(const char * filePath, long fileSize);
		bool loadFile(const char * filePath);
		bool saveFile(const char * filePath, long fileSize);
		void clearLoadedFile();
		
		bool writeLong(long data, long offset);
		bool writeShort(short data, long offset);
		bool writeByte(char data, long offset);
		bool writeFloat(float data, long offset);
		bool writeDouble(double data, long offset);
	
		void readLong(unsigned long * variable, long offset);
		void readShort(unsigned short * variable, long offset);
		void readByte(unsigned char * variable, long offset);
		void readFloat(float * variable, long offset);
		void readDouble(double * variable, long offset);
};

#endif