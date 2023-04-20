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
	g++ -c $(SOURCE).cpp *.hpp *.cpp -I $(INCLUDE)
link:
	g++ $(CXXFLAGS) $(SOURCE).o button.o menu.o databasemenu.o arrowline.o LLNode.o SLL.o Textbox.o Image.o Highlight.o -o main -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)
run:
	./${SOURCE}.exe