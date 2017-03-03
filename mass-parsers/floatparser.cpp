#include <cstdlib>
#include <cstdio>
#include "data.h"

int main(int argc, char * argv[])
{
	if(argc<2) return 0;
	Data * data = new Data();
	long length = data->loadFile(argv[1]);
	long n = length/4;
	float x[n];
	data->readFloatArray(x, 0, n);
	for(long i = 0; i<n; i++)
	{
		printf("%f\n", x[i]);
	}
	delete data;
	return 0;
}