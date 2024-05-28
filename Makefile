all: build run

build:
	g++ -g --std=c++11 -Iinclude -Llib ./src/*.cpp ./include/imgui/*.cpp ./src/glad.c -lglfw3dll -lassimp.dll -o ./bin/opengl.exe

run:
	./bin/opengl.exe