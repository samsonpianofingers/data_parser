 #include <cstdlib>
#include <cstdio>
#include "data.h"
// Program to test class functions

void testLittle(){
	puts("[*] Testing object constructor Data(littleEndian)");
	Endian e = littleEndian;
	Data * data = new Data(e);
	if(data->isCompatible())
	{puts("[*] System that compiled this is compatible");}
	else
	{
		puts("[*] System that compiled this is not combatible");
		puts("[*] This means types are the wrong byte size for this software.");
		return;
	}
	
	if(data->isLittleEndian()) puts("[*] Running in Little Endian Mode");
	if(data->isBigEndian()) puts("[*] Running in Big Endian Mode");
	
	printf("[*] Data Object at -> %X\n", data);
	puts("[*] Testing loadFile()");
	if(data->loadFile("filetest1")) {
		puts("[*] Success!");
	}
	else {
		puts("[*] Failed to open file"); return;
	}

	// Testing reading unsigned longs, shorts, bytes and then floats and doubles
	unsigned long l = 0;
	puts("[*] Testing readLong()");
	data->readLong(&l, 0);
	if(l == 1000)
	{printf("[*] Success! Returned correct value of %d\n", l);}
	else {
		printf("[*] Failed: Returned %d", l);
	}

	unsigned short s = 0;
	puts("[*] Testing readShort()");
	data->readShort(&s, 4);
	if(s == 500) {
		printf("[*] Success! Returned correct value of %d\n",s);
	}
	else {
		printf("[*] Failure: Returned %d\n", s);
	}

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
	if(d == 3.14159){
		printf("[*] Success! Returned correct value of %f\n",d);
	}
	else {
		printf("[*] Failure: Returned %f\n", d	);
	}
	
	// Testing reading arrays
	
	unsigned long l3 [3];
	puts("[*] Testing readLongArray()");
	data->readLongArray(l3,19,3);
	if(l3[0] == 100 && l3[1] == 200 && l3[2] == 300) {
		printf("[*] Success! values are %d, %d, %d\n", l3[0], l3[1], l3[2]);
	}
	else {
		printf("[*] Failure! values are %d, %d, %d\n", l3[0], l3[1], l3[2]);
	}
	
	unsigned short s3 [3];
	puts("[*] Testing readShortArray()");
	data->readShortArray(s3,31,3);
	
	if(s3[0] == 100 && s3[1] == 200 && s3[2] == 300) {
		printf("[*] Success! values are %d, %d, %d\n", s3[0], s3[1], s3[2]);
	}
	else {
		printf("[*] Failure! values are %d, %d, %d\n", s3[0], s3[1], s3[2]);
	}
	
	unsigned char c3 [3];
	puts("[*] Testing readByteArray()");
	data->readByteArray(c3,37, 3);
	
	if(c3[0] == 1 && c3[1] == 2 && c3[2] == 3) {
		printf("[*] Success! values are %d, %d, %d\n", c3[0], c3[1], c3[2]);
	}
	else {
		printf("[*] Failure! values are %d, %d, %d\n", c3[0], c3[1], c3[2]);
	}
	
	puts("[*] Testing closeCurrentFile();");
	data->closeCurrentFile();
	// Testing writing data to new file
	puts("[*] Testing createNewFile()");
	if(data->createNewFile("newfile1.bin", 256)) {
		puts("[*] New file was created and loaded!");
	}
	else {
		puts("[*] Failed to create/open new file");
		return;
	}
	
	puts("[*] Testing writeLong();");
	unsigned long testlong = 32;
	if(data->writeLong(testlong, 0)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeLong() signed overload;");
	long stestlong = 32;
	if(data->writeLong(stestlong, 0)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	
	puts("[*] Testing writeShort();");
	unsigned short testshort = 32;
	if(data->writeShort(testshort, 4)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeShort() signed overload");
	short stestshort = 32;
	if(data->writeShort(stestshort, 4)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeByte();");
	unsigned char testbyte = 32;
	if(data->writeByte(testbyte, 6)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeByte() signed overload;");
	char stestbyte = 32;
	if(data->writeByte(stestbyte, 6)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeLongArray();");
	unsigned long larray[] = {32,64,128};
	if(data->writeLongArray(larray, 7,3)){
		puts("[*] Success");	   
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeLongArray() signed overload;");
	long slarray[] = {32,64,128};
	if(data->writeLongArray(slarray, 7,3)){
		puts("[*] Success");	   
	}
	
	else {
		 puts("[*] Failure!");
	}
	   
	puts("[*] Testing writeShortArray();");
	unsigned short sarray[] = {32,64,128};
	if(data->writeShortArray(sarray, 19,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeShortArray() signed overload;");
	short ssarray[] = {32,64,128};
	if(data->writeShortArray(ssarray, 19,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	
	puts("[*] Testing writeByteArray();");
	unsigned char barray[] = {32,64,128};
	if(data->writeByteArray(barray, 25,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeByteArray() signed overload;");
	char sbarray[] = {32,64,128};
	if(data->writeByteArray(sbarray, 25,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}	  
	
	puts("[*] Testing writeFloat();");
	float testfloat = 3.141;
	if(data->writeFloat(testfloat,28))
	{
		puts("[*] Success");
	}
	else {
		 puts("[*] Failure!");
	}
	   
	puts("[*] Testing writeDouble();");
	double testdouble = 3.141592;
	if(data->writeDouble(testdouble,32))
	{
		puts("[*] Success");
	}
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeFloatArray();");
	float farray[] = {1,1.5,2.5};
	if(data->writeFloatArray(farray, 40,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeDoubleArray();");
	double darray[] = {1,1.5,2.5};
	if(data->writeDoubleArray(darray, 52,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}

	puts("[*] Testing saveCurrentFile();");
	if(data->saveCurrentFile()){
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	data->~Data();
}
void testBig(){
	puts("[*] Testing object constructor Data(bigEndian)");
	Endian e = bigEndian;
	Data * data = new Data(e);
	if(data->isCompatible())
	{puts("[*] System that compiled this is compatible");}
	else
	{
		puts("[*] System that compiled this is not combatible");
		puts("[*] This means types are the wrong byte size for this software.");
		return;
	}
	
	if(data->isLittleEndian()) puts("[*] Running in Little Endian Mode");
	if(data->isBigEndian()) puts("[*] Running in Big Endian Mode");
	
	printf("[*] Data Object at -> %X\n", data);
	puts("[*] Testing loadFile()");
	if(data->loadFile("filetest2")) {
		puts("[*] Success!");
	}
	else {
		puts("[*] Failed to open file"); return;
	}

	// Testing reading unsigned longs, shorts, bytes and then floats and doubles
	unsigned long l = 0;
	puts("[*] Testing readLong()");
	data->readLong(&l, 0);
	if(l == 1000)
	{printf("[*] Success! Returned correct value of %d\n", l);}
	else {
		printf("[*] Failed: Returned %d", l);
	}

	unsigned short s = 0;
	puts("[*] Testing readShort()");
	data->readShort(&s, 4);
	if(s == 500) {
		printf("[*] Success! Returned correct value of %d\n",s);
	}
	else {
		printf("[*] Failure: Returned %d\n", s);
	}

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
	if(d == 3.14159){
		printf("[*] Success! Returned correct value of %f\n",d);
	}
	else {
		printf("[*] Failure: Returned %f\n", d	);
	}
	
	// Testing reading arrays
	
	unsigned long l3 [3];
	puts("[*] Testing readLongArray()");
	data->readLongArray(l3,19,3);
	if(l3[0] == 100 && l3[1] == 200 && l3[2] == 300) {
		printf("[*] Success! values are %d, %d, %d\n", l3[0], l3[1], l3[2]);
	}
	else {
		printf("[*] Failure! values are %d, %d, %d\n", l3[0], l3[1], l3[2]);
	}
	
	unsigned short s3 [3];
	puts("[*] Testing readShortArray()");
	data->readShortArray(s3,31,3);
	
	if(s3[0] == 100 && s3[1] == 200 && s3[2] == 300) {
		printf("[*] Success! values are %d, %d, %d\n", s3[0], s3[1], s3[2]);
	}
	else {
		printf("[*] Failure! values are %d, %d, %d\n", s3[0], s3[1], s3[2]);
	}
	
	unsigned char c3 [3];
	puts("[*] Testing readByteArray()");
	data->readByteArray(c3,37, 3);
	
	if(c3[0] == 1 && c3[1] == 2 && c3[2] == 3) {
		printf("[*] Success! values are %d, %d, %d\n", c3[0], c3[1], c3[2]);
	}
	else {
		printf("[*] Failure! values are %d, %d, %d\n", c3[0], c3[1], c3[2]);
	}
	
	puts("[*] Testing closeCurrentFile();");
	data->closeCurrentFile();
	// Testing writing data to new file
	puts("[*] Testing createNewFile()");
	if(data->createNewFile("newfile2.bin", 256)) {
		puts("[*] New file was created and loaded!");
	}
	else {
		puts("[*] Failed to create/open new file");
		return;
	}
	
	puts("[*] Testing writeLong();");
	unsigned long testlong = 32;
	if(data->writeLong(testlong, 0)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeLong() signed overload;");
	long stestlong = 32;
	if(data->writeLong(stestlong, 0)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	
	puts("[*] Testing writeShort();");
	unsigned short testshort = 32;
	if(data->writeShort(testshort, 4)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeShort() signed overload");
	short stestshort = 32;
	if(data->writeShort(stestshort, 4)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeByte();");
	unsigned char testbyte = 32;
	if(data->writeByte(testbyte, 6)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeByte() signed overload;");
	char stestbyte = 32;
	if(data->writeByte(stestbyte, 6)) {
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	
	puts("[*] Testing writeLongArray();");
	unsigned long larray[] = {32,64,128};
	if(data->writeLongArray(larray, 7,3)){
		puts("[*] Success");	   
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeLongArray() signed overload;");
	long slarray[] = {32,64,128};
	if(data->writeLongArray(slarray, 7,3)){
		puts("[*] Success");	   
	}
	
	else {
		 puts("[*] Failure!");
	}
	   
	puts("[*] Testing writeShortArray();");
	unsigned short sarray[] = {32,64,128};
	if(data->writeShortArray(sarray, 19,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeShortArray() signed overload;");
	short ssarray[] = {32,64,128};
	if(data->writeShortArray(ssarray, 19,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	
	puts("[*] Testing writeByteArray();");
	unsigned char barray[] = {32,64,128};
	if(data->writeByteArray(barray, 25,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeByteArray() signed overload;");
	char sbarray[] = {32,64,128};
	if(data->writeByteArray(sbarray, 25,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}	  
	
	puts("[*] Testing writeFloat();");
	float testfloat = 3.141;
	if(data->writeFloat(testfloat,28))
	{
		puts("[*] Success");
	}
	else {
		 puts("[*] Failure!");
	}
	   
	puts("[*] Testing writeDouble();");
	double testdouble = 3.141592;
	if(data->writeDouble(testdouble,32))
	{
		puts("[*] Success");
	}
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeFloatArray();");
	float farray[] = {1,1.5,2.5};
	if(data->writeFloatArray(farray, 40,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}
	
	puts("[*] Testing writeDoubleArray();");
	double darray[] = {1,1.5,2.5};
	if(data->writeDoubleArray(darray, 52,3)){
		puts("[*] Success");
	}
	
	else {
		 puts("[*] Failure!");
	}

	puts("[*] Testing saveCurrentFile();");
	if(data->saveCurrentFile()){
		puts("[*] Success!");
	}
	else
	{
		puts("[*] Failure!");
	}
	data->~Data();
}

int main(int argc, char * argv[])
{
	testLittle();
	testBig();
	return 0;
}