#include <cstdlib>
#include <cstdio>
#include "data.h"
int main(int argc, char * argv[])
{
	Endian e = littleEndian;
	Data * data = new Data(e);
	data->loadFile("filetest");
	unsigned long l = 0;
	data->readLong(&l, 0);
	data->setEndianness(bigEndian);
	unsigned long b = 0;
	data->readLong(&b, 0);
	delete data;
	return 0;
}
