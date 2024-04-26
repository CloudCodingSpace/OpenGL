@echo off

g++ -g -Iinclude -Llib src/*.cpp src/*.c include/imgui/*.cpp -lglfw3dll -lassimp.dll -o opengl.exe

opengl.exe