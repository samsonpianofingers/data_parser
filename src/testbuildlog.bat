@echo off
For /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set mydate=%%c-%%a-%%b)
For /f "tokens=1-2 delims=/:" %%a in ('time /t') do (set mytime=%%a%)
g++ testapp.cpp data.cpp -o .\bin\testapp.exe 2> .\logs\errors_%mydate%_.txt
type .\logs\errors_%mydate%_.txt