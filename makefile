# This is makefile for SFML C++

path = C:\SFML-2.5.1
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
CXXFLAGS =
SFMLFLAGS =
SOURCE = main
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system
#=======================================================================================#
	
all: compile link run
compile:
	g++ -c $(SOURCE).cpp -I\Components\*.hpp -I $(INCLUDE) 
link:
	g++ $(CXXFLAGS) $(SOURCE).o -o main -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)
run:
	./main.exe