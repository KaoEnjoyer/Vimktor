main: 
	g++ main.cpp filemanager.cpp renderer.cpp window.cpp -o vimktor -lncurses -std=c++11
debug:
	g++ main.cpp renderer.cpp window.cpp -o vimktor -lncurses -Wall -std=c++11

