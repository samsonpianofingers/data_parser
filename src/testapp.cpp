#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main(int argc, char * argv[])
{
	Endian e = littleEndian;
	Data * data = new Data(e);
	for(int i = 0; i<100000; i++){
	data->loadFile("C:/Windows/system32/cmd.exe");
	}
	system("pause");
	delete data;
}
