main: 
	g++ main.cpp renderer.cpp window.cpp -o vimktor -lncurses
debug:
	g++ main.cpp renderer.cpp window.cpp -o vimktor -lncurses -Wall 

