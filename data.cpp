//class for reading and writing data to and from files

#include <stdlib.h>
#include <stdio.h>
#include "data.h"
//Endian - littleEndian , bigEndian
Data::Data(Endian Endianness)
{
	setEndianness(Endianness);
	fileLoaded = false;
}

Data::Data(Endian Endianness, const char * filePath)
{
	setEndianness(Endianness);
	loadFile(filePath);
}

void Data::clearLoadedFile(){
	delete [] buffer;
	delete file;
	fileLoaded = false;
}

long Data::getFileLength()
{
	if(file!=NULL){
		long len = 0;
		fseek(file, 0,SEEK_END);
		len = ftell(file);
		rewind(file);
		return len;
	}
	else
	{
		return ERR_NULLPTR;
	}
}

void Data::setEndianness(bool e){
	if(e==true){
		endianMode = littleEndian;
	}
	else
	{
		endianMode = bigEndian;
	}
	
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


bool Data::loadFile(const char * filePath){
	if(fileLoaded == false){
		file = fopen(filePath, "rb");
		fileLength = getFileLength();
		if(file!=NULL)
		{
			buffer = new unsigned char[fileLength];
			fread(buffer, 1, fileLength, file);
			fclose(file);
			fileLoaded = true;
			return true;
		}
	}
	return false;
	
}

bool Data::saveFile(const char * filePath, long fileSize){
	if(fileLoaded){
		file = fopen(filePath, "wb");
		fwrite(buffer, sizeof(char), fileSize, file);
		if(ferror(file)){
			//Failed to save
			return false;
		}
		fclose(file);
		return true;
	}
	return false;
}

bool Data::createNewFile(const char * filePath, long fileSize){
	if(!fileLoaded)
	{
		file = fopen(filePath, "rb+");
		if(file == NULL) //if file does not already exist, create it
		{
			file = fopen(filePath, "wb");
			if(file!=NULL){
				buffer = new unsigned char[fileSize];
				fileLoaded = true;
				fclose(file);
				return true;
			}
		}
	}
	return false;
}


bool Data::writeLong(long data, long offset){
	if(endianMode == littleEndian && fileLoaded){
		buffer[offset+3] = data & 0xff;
		buffer[offset+2] = data >> 8;
		buffer[offset+1] = data >> 16;
		buffer[offset] = data >> 24;
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{

		buffer[offset] = data & 0xff;
		buffer[offset+1] = data >> 8;
		buffer[offset+2] = data >> 16;
		buffer[offset+3] = data >> 24;
		return true;
	}
	return false;
}

bool Data::writeShort(short data, long offset){
	if(endianMode == littleEndian){
		buffer[offset+1] = data & 0xff;
		buffer[offset] = data >> 8;
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		buffer[offset] = data & 0xff;
		buffer[offset+1] = data >> 8;
		return true;
	}
	return false;
}

bool Data::writeByte(char data, long offset){
	if(fileLoaded == true)
	{
		buffer[offset] = data;
		return true;
	}
	return false;	
}


void Data::readLong(unsigned long * variable, long offset){
	long result = 0;
	if(endianMode == littleEndian && fileLoaded){
		
		result += buffer[offset+3];
		result += (buffer[offset+2]) << 8;
		result += (buffer[offset+1]) << 16;
		result += (buffer[offset]) << 24;
		*variable = result;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		result += buffer[offset];
		result += buffer[offset+1]<< 8;
		result += buffer[offset+2]<< 16;
		result += buffer[offset+3]<< 24;
		*variable = result;
	}
	
}
	
void Data::readShort(unsigned short * variable, long offset){
	short result = 0;
	if(endianMode == littleEndian && fileLoaded){
		result += buffer[offset+1];
		result += buffer[offset] << 8;
		*variable = result;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		result += buffer[offset];
		result += (buffer[offset+1]) << 8;
		*variable = result;
	}
}

void Data::readByte(unsigned char * variable, long offset){
	if(fileLoaded == true)
	{
		*variable = buffer[offset];
	}
}


	
void Data::readFloat(float * variable, long offset){
	union{   float d; char bytes[sizeof(float)]; }convert;
	if(endianMode == littleEndian && fileLoaded){
		convert.bytes[0] = buffer[offset+3];
		convert.bytes[1] = buffer[offset+2];
		convert.bytes[2] = buffer[offset+1];
		convert.bytes[3] = buffer[offset];
		*variable = convert.d;

	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		convert.bytes[3] = buffer[offset+3];
		convert.bytes[2] = buffer[offset+2];
		convert.bytes[1] = buffer[offset+1];
		convert.bytes[0] = buffer[offset+0];
		*variable = convert.d;
	}
}

bool Data::writeFloat(float data, long offset){
	union{   float d; char bytes[sizeof(float)]; }convert;
	convert.d = data;
	if(endianMode == littleEndian && fileLoaded){
		buffer[offset] = convert.bytes[3];
		buffer[offset+1] = convert.bytes[2];
		buffer[offset+2] = convert.bytes[1];
		buffer[offset+3] = convert.bytes[0];
		return true;
	}
	else if (endianMode == bigEndian && fileLoaded)
	{
		buffer[offset+3] = convert.bytes[3];
		buffer[offset+2] = convert.bytes[2];
		buffer[offset+1] = convert.bytes[1];
		buffer[offset] = convert.bytes[0];
		return true;
	}
	return false;
	
}
	
void Data::readDouble(double * variable, long offset){
	union{   double d; char bytes[sizeof(double)]; }convert;
	if(endianMode == littleEndian && fileLoaded){
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
	else if (endianMode == bigEndian && fileLoaded)
	{
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
}

bool Data::writeDouble(double data, long offset){
	union{   double d; char bytes[sizeof(double)]; }convert;
	convert.d = data;
	if(endianMode == littleEndian && fileLoaded){
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
	else if (endianMode == bigEndian && fileLoaded)
	{
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
	return false;
}