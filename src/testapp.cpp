#include <cstdlib>
#include <cstdio>
#include "data.h"
// Program to test class functions
int main(int argc, char * argv[])
{
	puts("[*] Testing object constructor without arguments - Data()");
	Data * data = new Data();
	if(data->isCompatible())
	{puts("[*] System that compiled this is compatible");}
	else
	{
		puts("[*] System that compiled this is not combatible");
		puts("[*] This means types are the wrong byte size for this software.");
	}
	
	if(data->isLittleEndian()) puts("[*] Running in Little Endian Mode");
	if(data->isBigEndian()) puts("[*] Running in Big Endian Mode");
	
	printf("[*] Data Object at -> %X\n", data);
	puts("[*] Testing loadFile()");
	if(data->loadFile("filetest"))
	{puts("[*] Success!");}
	else
	{puts("[*] Failed to open file");}

	// Testing reading unsigned longs, shorts, bytes and then floats and doubles
	unsigned long l = 0;
	puts("[*] Testing readLong()");
	data->readLong(&l, 0);
	if(l == 1000)
	{printf("[*] Success! Returned correct value of %d\n", l);}
	else
	{ printf("[*] Failed: Returned %d", l); }

	unsigned short s = 0;
	puts("[*] Testing readShort()");
	data->readShort(&s, 4);
	if(s == 500)
	{printf("[*] Success! Returned correct value of %d\n",s);}
	else
	{printf("[*] Failure: Returned %d\n", s);}

	unsigned char c = 0;
	puts("[*] Testing readByte()");
	data->readByte(&c, 6);
	if(c == 42)
	{printf("[*] Success! Returned correct value of %d\n",c);}
	else
	{printf("[*] Failure: Returned %d\n", c	);}

	float f = 0;
	puts("[*] Testing readFloat()");
	data->readFloat(&f, 7);
	if(f == 44.2400016784668f)
	{printf("[*] Success! Returned correct value of %f\n",f);}
	else
	{printf("[*] Failure: Returned %f\n", f	);}

	double d = 0;
	puts("[*] Testing readDouble()");
	data->readDouble(&d, 11);
	if(d == 3.14159)
	{printf("[*] Success! Returned correct value of %f\n",d);}
	else
	{printf("[*] Failure: Returned %f\n", d	);}
	
	unsigned long l3 [3];
	puts("[*] Testing readLongArray()");
	data->readLongArray(l3,19,3);
	if(l3[0] == 100 && l3[1] == 200 && l3[2] == 300)
	{
		printf("[*] Success! values are %d, %d, %d\n", l3[0], l3[1], l3[2]);
	}
	else
	{
		printf("[*] Failure! values are %d, %d, %d\n", l3[0], l3[1], l3[2]);
	}
	
	unsigned short s3 [3];
	puts("[*] Testing readShortArray()");
	data->readShortArray(s3,31,3);
	
	if(s3[0] == 100 && s3[1] == 200 && s3[2] == 300)
	{
		printf("[*] Success! values are %d, %d, %d\n", s3[0], s3[1], s3[2]);
	}
	else
	{
		printf("[*] Failure! values are %d, %d, %d\n", s3[0], s3[1], s3[2]);
	}
	
	unsigned char c3 [3];
	puts("[*] Testing readByteArray()");
	data->readByteArray(c3,37, 3);
	
	if(c3[0] == 1 && c3[1] == 2 && c3[2] == 3)
	{
		printf("[*] Success! values are %d, %d, %d\n", c3[0], c3[1], c3[2]);
	}
	else
	{
		printf("[*] Failure! values are %d, %d, %d\n", c3[0], c3[1], c3[2]);
	}

	delete data;
	return 0;
}