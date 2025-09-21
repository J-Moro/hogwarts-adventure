@echo off
setlocal enabledelayedexpansion

set FILES=
for %%f in (*.cpp) do (
    set FILES=!FILES! %%f
)

g++ !FILES! -o main.exe
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)
main.exe