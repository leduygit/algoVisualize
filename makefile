# This is makefile for SFML C++

path = C:\SFML-2.5.1
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
CXXFLAGS =
SFMLFLAGS =
SOURCE = main.cpp
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system
#=======================================================================================#

all: compile link run
compile:
	g++ -c Button.hpp Menu.hpp *.cpp -I $(INCLUDE)
link:
	g++  *.cpp -o main -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)
run:
	./main.exe