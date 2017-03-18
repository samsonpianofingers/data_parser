#include <cstdlib>
#include <cstdio>
#include "data.h"

Data::Data(){
	// Auto Select system endianess during runtime (almost always little endian)
	// Just means you dont have to pass any arguments
	int x = 1;
	// little endian if true
	if(*(char *)&x == 1)
	{ endianMode = littleEndian;}
	else
	{endianMode = bigEndian;}
	fileLoaded = false;
}

Data::~Data(){
	delete [] buffer;
	delete currentFile;
}

Data::Data(Endian Endianness)
{
	endianMode = Endianness;
	fileLoaded = false;
}

Data::Data(Endian Endianness, const char * filePath)
{
	setEndianness(Endianness);
	loadFile(filePath);
}

long Data::getFileLength()
{
	if(currentFile!=NULL){
		long len = 0;
		std::fseek(currentFile, 0,SEEK_END);
		len = std::ftell(currentFile);
		std::rewind(currentFile);
		return len;
	}
	else
	{
		return 0;
	}
}

void Data::setEndianness(Endian e){
	endianMode = e;
}

bool Data::isLittleEndian(){
	if(endianMode==littleEndian){
		return true;
	}
	return false;
}

bool Data::isBigEndian(){
	if(endianMode==littleEndian){
		return false;
	}
	return true;
}

bool Data::isCompatible(){
	//NOTE: Compiler decides this on compile time, after that it is permanently false or true in the exe.
	if(
	SHORTsz == 2 &&
	LONGsz == 4 &&
	FLOATsz == 4 &&
	DOUBLEsz == 8
	) return true;
	else
	{return false;}
}


long Data::loadFile(const char * filePath){
	if(fileLoaded){
		delete [] buffer;
		fileLoaded = false;
	}
	if(!fileLoaded){
		currentFile = std::fopen(filePath, "rb");
		fileLength = getFileLength();
		if(currentFile!=NULL)
		{
			buffer = new unsigned char[fileLength];
			std::fread(buffer, 1, fileLength, currentFile);
			fileLoaded = true;
			return fileLength;
		}
	}
	return 0;
	
}

bool Data::saveFile(const char * filePath, long fileSize){
	if(fileLoaded){
		FILE * file = std::fopen(filePath, "wb");
		std::fwrite(buffer, sizeof(char), fileSize, file);
		if(std::ferror(file)){
			//Failed to save
			return false;
		}
		std::fclose(file);
		return true;
	}
	return false;
}

bool Data::saveCurrentFile()
{
	if(fileLoaded)
	{
		std::fwrite(buffer, sizeof(char), fileLength, currentFile);
		if(std::ferror(currentFile)){
			//Failed to save
			return false;
		}
		return true;
	}
}

void Data::closeCurrentFile(){
	if(fileLoaded)
	{
		fclose(currentFile);
		delete [] buffer;
		fileLoaded = false;
	}
}

bool Data::createNewFile(const char * filePath, long fileSize){
	if(fileLoaded){
		closeCurrentFile();
	}
	currentFile = std::fopen(filePath, "rb+");
	if(currentFile == NULL) //if file does not already exist, create it
	{
		currentFile = std::fopen(filePath, "wb");
		if(currentFile!=NULL){
			buffer = new unsigned char[fileSize];
			for(long i = 0; i<fileSize; i++){
				buffer[i] = 0;
			}
			fileLoaded = true;
			fileLength = fileSize;
			return true;
		}
	}
	return false;
}

bool Data::writeLong(long data, long offset){
	if(offset+LONGsz>fileLength) return false;
	if(endianMode == littleEndian && fileLoaded){
		buffer[offset] = data & 0xff;
		buffer[offset+1] = data >> 8;
		buffer[offset+2] = data >> 16;
		buffer[offset+3] = data >> 24;
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		buffer[offset+3] = data & 0xff;
		buffer[offset+2] = data >> 8;
		buffer[offset+1] = data >> 16;
		buffer[offset] = data >> 24;
		return true;
	}
	return false;
}

bool Data::writeShort(short data, long offset){
	if(offset+SHORTsz>fileLength) return false;
	if(endianMode == littleEndian){
		buffer[offset] = data & 0xff;
		buffer[offset+1] = data >> 8;
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		buffer[offset+1] = data & 0xff;
		buffer[offset] = data >> 8;
		return true;
	}
	return false;
}

bool Data::writeByte(char data, long offset){
	if(offset>fileLength) return false;
	if(fileLoaded == true)
	{
		buffer[offset] = data;
		return true;
	}
	return false;	
}

bool Data::writeLong(unsigned long data, long offset){
	if(offset+LONGsz>fileLength) return false;
	if(endianMode == littleEndian && fileLoaded){
		buffer[offset] = data & 0xff;
		buffer[offset+1] = data >> 8;
		buffer[offset+2] = data >> 16;
		buffer[offset+3] = data >> 24;
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		buffer[offset+3] = data & 0xff;
		buffer[offset+2] = data >> 8;
		buffer[offset+1] = data >> 16;
		buffer[offset] = data >> 24;
		return true;
	}
	return false;
}

bool Data::writeShort(unsigned short data, long offset){
	if(offset+SHORTsz>fileLength) return false;
	if(endianMode == littleEndian){
		buffer[offset] = data & 0xff;
		buffer[offset+1] = data >> 8;
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{

		buffer[offset+1] = data & 0xff;
		buffer[offset] = data >> 8;
		return true;
	}
	return false;
}

bool Data::writeByte(unsigned char data, long offset){
	if(offset>fileLength) return false;
	if(fileLoaded == true)
	{
		buffer[offset] = data;
		return true;
	}
	return false;	
}

bool Data::readLong(unsigned long * variable, long offset){
	if(offset+LONGsz>fileLength) return false;
	long result = 0;
	if(endianMode == littleEndian && fileLoaded)
	{
		result += buffer[offset];
		result += buffer[offset+1]<< 8;
		result += buffer[offset+2]<< 16;
		result += buffer[offset+3]<< 24;
		*variable = result;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		result += buffer[offset+3];
		result += (buffer[offset+2]) << 8;
		result += (buffer[offset+1]) << 16;
		result += (buffer[offset]) << 24;
		*variable = result;
	}
	
}
	
bool Data::readShort(unsigned short * variable, long offset){
	if(offset+SHORTsz>fileLength) return false;
	short result = 0;
	if(endianMode == littleEndian && fileLoaded){
		result += buffer[offset];
		result += (buffer[offset+1]) << 8;
		*variable = result;

	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		result += buffer[offset+1];
		result += buffer[offset] << 8;
		*variable = result;
	}
}

bool Data::readByte(unsigned char * variable, long offset){
	if(offset+1>fileLength) return false;
	if(fileLoaded == true)
	{
		*variable = buffer[offset];
		return true;
	}
}

bool Data::readFloat(float * variable, long offset){
	if(offset+FLOATsz>fileLength) return false;
	union{   float d; char bytes[FLOATsz]; }convert;
	if(endianMode == littleEndian && fileLoaded){
		convert.bytes[3] = buffer[offset+3];
		convert.bytes[2] = buffer[offset+2];
		convert.bytes[1] = buffer[offset+1];
		convert.bytes[0] = buffer[offset+0];
		*variable = convert.d;
		return true;


	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		convert.bytes[0] = buffer[offset + 3];
		convert.bytes[1] = buffer[offset + 2];
		convert.bytes[2] = buffer[offset + 1];
		convert.bytes[3] = buffer[offset];
		*variable = convert.d;
		return true;
	}
	return false;
}

bool Data::writeFloat(float data, long offset){
	if(offset+FLOATsz>fileLength) return false;
	union{   float d; char bytes[FLOATsz]; }convert;
	convert.d = data;
	if(endianMode == littleEndian && fileLoaded){
		buffer[offset+3] = convert.bytes[3];
		buffer[offset+2] = convert.bytes[2];
		buffer[offset+1] = convert.bytes[1];
		buffer[offset] = convert.bytes[0];
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		buffer[offset] = convert.bytes[3];
		buffer[offset+1] = convert.bytes[2];
		buffer[offset+2] = convert.bytes[1];
		buffer[offset+3] = convert.bytes[0];
		return true;
	}
	return false;
	
}
	
bool Data::readDouble(double * variable, long offset){
	if(offset+DOUBLEsz>fileLength) return false;
	union{   double d; char bytes[DOUBLEsz]; }convert;
	if(endianMode == littleEndian && fileLoaded){
		convert.bytes[7] = buffer[offset+7];
		convert.bytes[6] = buffer[offset+6];
		convert.bytes[5] = buffer[offset+5];
		convert.bytes[4] = buffer[offset+4];
		convert.bytes[3] = buffer[offset+3];
		convert.bytes[2] = buffer[offset+2];
		convert.bytes[1] = buffer[offset+1];
		convert.bytes[0] = buffer[offset];
		*variable = convert.d;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		convert.bytes[0] = buffer[offset+7];
		convert.bytes[1] = buffer[offset+6];
		convert.bytes[2] = buffer[offset+5];
		convert.bytes[3] = buffer[offset+4];
		convert.bytes[4] = buffer[offset+3];
		convert.bytes[5] = buffer[offset+2];
		convert.bytes[6] = buffer[offset+1];
		convert.bytes[7] = buffer[offset];
		*variable = convert.d;
	}
}

bool Data::writeDouble(double data, long offset){
	if(offset+DOUBLEsz>fileLength) return false;
	union{   double d; char bytes[DOUBLEsz]; }convert;
	convert.d = data;
	if(endianMode == littleEndian && fileLoaded){
		buffer[offset] = convert.bytes[0];
		buffer[offset+1] = convert.bytes[1];
		buffer[offset+2] = convert.bytes[2];
		buffer[offset+3] = convert.bytes[3];
		buffer[offset+4] = convert.bytes[4];
		buffer[offset+5] = convert.bytes[5];
		buffer[offset+6] = convert.bytes[6];
		buffer[offset+7] = convert.bytes[7];
		return true;

	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		buffer[offset+7] = convert.bytes[0];
		buffer[offset+6] = convert.bytes[1];
		buffer[offset+5] = convert.bytes[2];
		buffer[offset+4] = convert.bytes[3];
		buffer[offset+3] = convert.bytes[4];
		buffer[offset+2] = convert.bytes[5];
		buffer[offset+1] = convert.bytes[6];
		buffer[offset] = convert.bytes[7];
		return true;
	}
	return false;
}

bool Data::readByteArray(unsigned char array[], long offset, long length)
{
	if(offset+length>fileLength) return false;
	for(int i = 0; i<length; i++)
	{
		array[i] = buffer[offset+i];
	}
	return true;
}

bool Data::readShortArray(unsigned short array[], long offset, long nShorts)
{
	int check = offset + (SHORTsz*nShorts);
	if(check>fileLength) return false;
	for(int i = 0; i<nShorts; i++){
		unsigned short x = 0;
		readShort(&x,offset+i*SHORTsz);
		array[i]=x;
	}
	return true;
}

bool Data::readLongArray(unsigned long array[], long offset, long nLongs)
{
	int check = offset + (LONGsz*nLongs);
	if(check>fileLength) return false;
	for(int i = 0; i<nLongs; i++){
		unsigned long x = 0;
		readLong(&x,offset+i*LONGsz);
		array[i]=x;
	}
	return true;
}

bool Data::readFloatArray(float array[], long offset, long nFloats)
{
	int check = offset + (FLOATsz*nFloats);
	if(check>fileLength) return false;
	for(int i = 0; i<nFloats; i++){
		float x = 0;
		readFloat(&x,offset+i*FLOATsz);
		array[i]=x;
	}
	return true;
}

bool Data::readDoubleArray(double array[], long offset, long nDoubles)
{
	int check = offset + (DOUBLEsz*nDoubles);
	if(check>fileLength) return false;
	for(int i = 0; i<nDoubles; i++){
		double x = 0;
		readDouble(&x,offset+i*DOUBLEsz);
		array[i]=x;
	}
	return true;
}

bool Data::writeByteArray(char array[], long offset, long length){
	if(offset+length>fileLength) return false;
	for(int i = 0; i<length; i++){
		char x = array[i];
		if(!writeByte(x,offset+i)) return false;
	}
	return true;
}

bool Data::writeShortArray(short array[], long offset, long nShorts){
	int check = offset + (SHORTsz*nShorts);
	if(check>fileLength) return false;
	for(int i = 0; i<nShorts; i++){
	short x = array[i];
		if(!writeShort(x,offset+i*SHORTsz)) return false;
	}
	return true;
}

bool Data::writeLongArray(long array[], long offset, long nLongs){
	int check = offset + (LONGsz*nLongs);
	if(check>fileLength) return false;
	for(int i = 0; i<nLongs; i++){
		long x = array[i];
		if(!writeLong(x,offset+(i*LONGsz))) return false;
	}
	return true;

}

bool Data::writeFloatArray(float array[], long offset, long nFloats){
	int check = offset + (FLOATsz*nFloats);
	if(check>fileLength) return false;
	for(int i = 0; i<nFloats; i++){
		float x = array[i];
		if(!writeFloat(x,offset+i*FLOATsz)) return false;
	}
	return true;
}

bool Data::writeDoubleArray(double array[], long offset, long nDoubles){
	int check = offset + (DOUBLEsz*nDoubles);
	if(check>fileLength) return false;
	for(int i = 0; i<nDoubles; i++){
		double x = array[i];
		if(!writeDouble(x,offset+i*DOUBLEsz)) return false;
	}
	return true;
}

bool Data::writeByteArray(unsigned char array[], long offset, long length){
	if(offset+length>fileLength) return false;
	for(int i = 0; i<length; i++){
		char x = array[i];
		if(!writeByte(x,offset+i)) return false;
	}
	return true;
}

bool Data::writeShortArray(unsigned short array[], long offset, long nShorts){
	int check = offset + (SHORTsz*nShorts);
	if(check>fileLength) return false;
	for(int i = 0; i<nShorts; i++){
	short x = array[i];
		if(!writeShort(x,offset+i*SHORTsz)) return false;
	}
	return true;
}

bool Data::writeLongArray(unsigned long array[], long offset, long nLongs){
	int check = offset + (LONGsz*nLongs);
	if(check>fileLength) return false;
	for(int i = 0; i<nLongs; i++){
		long x = array[i];
		if(!writeLong(x,offset+i*LONGsz)) return false;
	}
	return true;
}
