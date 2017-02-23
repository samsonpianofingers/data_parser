#include <cstdlib>
#include <cstdio>
#include "data.h"
int main(int argc, char * argv[])
{
	// File to test features
//	Endian e = littleEndian;
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

	delete data;
	return 0;
}
