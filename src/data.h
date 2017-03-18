#ifndef DATA_H
#define DATA_H

const unsigned int SHORTsz = sizeof(short);
const unsigned int LONGsz = sizeof(long);
const unsigned int FLOATsz = sizeof(float);
const unsigned int DOUBLEsz = sizeof(double);

enum Endian
{
	littleEndian=0,
	bigEndian=1
};

class Data
{
	private:
		Endian endianMode;
		FILE * currentFile;
		unsigned char * buffer;
		long fileLength;
		bool fileLoaded;
		long getFileLength();
	public:	
		Data();
		~Data();
		explicit Data(Endian Endianness); //ctor
		Data(Endian Endianness, const char * filePath); //ctor overload
		void setEndianness(Endian e); // Change endianess on the fly
		bool isLittleEndian();
		bool isBigEndian();
		//Checks if compiler/machine uses standard 32bit sizes for longs etc.
		bool isCompatible();
		
		
		// Creates a new file and allocs a buffer for read and write
		bool createNewFile(const char * filePath, long fileSize); 
		// Loads a file for read/write
		long loadFile(const char * filePath);
		// Saves the buffer to a file.
		bool saveFile(const char * filePath, long fileSize);
		// Saves buffer to current loaded file
		bool saveCurrentFile();
		void closeCurrentFile();
		
		bool writeByte(char data, long offset);
		bool writeShort(short data, long offset);
		bool writeLong(long data, long offset);
		bool writeFloat(float data, long offset);
		bool writeDouble(double data, long offset);
		
		//Unsigned overloads
		bool writeByte(unsigned char data, long offset);
		bool writeShort(unsigned short data, long offset);
		bool writeLong(unsigned long data, long offset);
	
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
		
		bool writeByteArray(char array[], long offset, long length);
		bool writeShortArray(short array[], long offset, long nShorts);
		bool writeLongArray(long array[], long offset, long nLongs);
		bool writeFloatArray(float array[], long offset, long nFloats);
		bool writeDoubleArray(double array[], long offset, long nDoubles);
		
		// Unsigned overloads
		bool writeByteArray(unsigned char array[], long offset, long length);
		bool writeShortArray(unsigned short array[], long offset, long nShorts);
		bool writeLongArray(unsigned long array[], long offset, long nLongs);
//		#ifdef GLM_H
		
//		#endif
};

#endif
