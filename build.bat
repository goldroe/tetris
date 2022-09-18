@echo off

pushd bin

CL -W4 -wd4053 -wd4101 -wd4100 -wd4189 -wd4201 -wd4996 -nologo -FC -Zi -MDd -I ..\deps\glad\include -I ..\deps\glfw\include -I ..\deps\HMM -I ..\deps\stb ..\src\tetris.c ..\deps\glad\src\glad.c -link -LIBPATH:C:\Dev\tetris\deps\glfw\bin\x64\lib-vc2019 user32.lib shell32.lib gdi32.lib opengl32.lib glfw3.lib

popd
