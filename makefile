FILES = main.cpp src/*.cpp
INC_PATH = ./third-party
LIB_PATH = ./lib
LIB = -lSOIL -lGL -lGLU -lglut -lGLM
OUTPUT = ./

all:
	g++ $(FILES) $(LIB) -L $(LIB_PATH) -I $(INC_PATH) -o $(OUTPUT)