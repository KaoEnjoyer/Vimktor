main: 
	g++ main.cpp filemanager.cpp renderer.cpp window.cpp -o vimktor -lncurses -std=c++17
debug:
	g++ main.cpp renderer.cpp window.cpp -o vimktor -lncurses -Wall -std=c++17

