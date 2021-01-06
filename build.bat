@echo off
cls
make clean
make -j 8
rd /s /q Build
pause