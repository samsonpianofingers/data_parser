@echo off
copy bin\filetest filetest
.\bin\testapp.exe
del filetest
pause