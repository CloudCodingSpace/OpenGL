@echo off
SetLocal EnableDelayedExpansion

set cxxs=
for /R %%f in (*.cpp) do (
	set cxxs=!cxxs! %%f
)

g++ -g -std=c++17 -Iinclude -Llib %cxxs% src/glad.c -lglfw3dll -lassimp.dll -o opengl.exe
