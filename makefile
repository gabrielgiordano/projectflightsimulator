FILES = main.cpp src/*.cpp
INC_PATH = ./third-party
LIB_PATH = ./lib
LIB = -lSOIL -lGL -lGLU -lglut -lGLM -ljpeg -lpng
OUTPUT = /home/gabriel/a.exe

all:
	g++ $(FILES) $(LIB) -L $(LIB_PATH) -I $(INC_PATH) -o $(OUTPUT)