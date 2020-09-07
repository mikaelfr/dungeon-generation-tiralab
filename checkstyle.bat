@echo off
for /F delims^=^ eol^= %%i in ('dir /s /b *.h *.cpp') do cstyle --config .cstyle %%i