#include "renderer.h"
#include <ncurses.h>
Renderer::Renderer() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, true);
  keypad(stdscr, true);
}

Renderer::~Renderer() { endwin(); }

void Renderer::renderWindow(Window &W) {
  wmove(stdscr, 0, 0);
  int x=0,y=0;
  for(auto el : W.m_buffer){
    for(auto str : el){
      x++;
      waddch(stdscr, str);
     
    }
    x = 0;
    wmove(stdscr,++y,x);
  }


  for (int y = 0; y < W.height(); y++) {
    for (int x = 0; x < W.width(); x++) {
//      wmove(stdscr, y, x);
    }
  }
  wmove(stdscr, W.m_cursor->y(), W.m_cursor->x());
  wrefresh(stdscr);
}

int Renderer::get_input() {
  int ch = wgetch(stdscr);
  return ch;
}
