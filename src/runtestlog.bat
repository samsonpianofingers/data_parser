@echo off
copy bin\filetest1 filetest1
copy bin\filetest2 filetest2
.\bin\testapp.exe > logs\log.txt
del filetest1
del filetest2
pause
del newfile1.bin
del newfile2.bin