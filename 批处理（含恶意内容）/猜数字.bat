@echo off
set/a rand=%random%%%100+1
set count=0
:loop1
set/a count+=1
set/p input=������һ��1-100�������:
if %input% equ %rand% (
echo �¶���
goto :end
)
if %input% lss %rand% (
echo С��
goto :loop1
)
if %input% gtr %rand% (
echo ����
goto :loop1
)

:end
pause >nul
exit