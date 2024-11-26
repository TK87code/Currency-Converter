@echo off
REM files are path from "build" folder, since we pushd

set files=..\code\main.c ..\code\tk_string.c

set libs=user32.lib

mkdir ..\build
pushd ..\build
cl /Zi %files% /link %libs% /OUT:"main.exe"
popd
