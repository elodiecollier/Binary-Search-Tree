run: compile
	./TreeType

compile: TreeType.cpp TreeDr.cpp
	g++ -Wall -std=c++11 -pedantic-errors -o TreeType TreeType.cpp TreeDr.cpp

clean:
	rm TreeType
