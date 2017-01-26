#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main(int argc, char * argv[])
{
	Endian e = littleEndian;
	Data * data = new Data(e);
	long length = data->loadFile("test");
	if(length)
	{
		unsigned long longs[length];
		if(data->readLongArray(longs,0,3)){
				printf("%d %d %d\n",longs[0],longs[1],longs[2]);
			}
	}
}
