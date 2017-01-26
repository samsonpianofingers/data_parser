#ifndef DATA_H
#define DATA_H

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
		long loadFile(const char * filePath);
		bool saveFile(const char * filePath, long fileSize);
		void clearLoadedFile();
		
		
		bool writeByte(char data, long offset);
		bool writeShort(short data, long offset);
		bool writeLong(long data, long offset);
		bool writeFloat(float data, long offset);
		bool writeDouble(double data, long offset);
	
		bool readByte(unsigned char * variable, long offset);
		bool readShort(unsigned short * variable, long offset);
		bool readLong(unsigned long * variable, long offset);
		bool readFloat(float * variable, long offset);
		bool readDouble(double * variable, long offset);
		
		bool readByteArray(unsigned char array[], long offset, long length);
		bool readShortArray(unsigned short array[], long offset, long nShorts);
		bool readLongArray(unsigned long array[], long offset, long nLongs);
		bool readFloatArray(float array[], long offset, long nFloats);
		bool readDoubleArray(double array[], long offset, long nDoubles);
		
		#ifdef GLM_H
		
		#endif
};

#endif