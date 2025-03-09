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
  curs_set(false);
  wmove(stdscr, 0, 0);
  for(auto el : W.m_buffer){
    for(auto str : el){
      waddch(stdscr, str);
    }
  }
  for (int y = 0; y < W.height(); y++) {
    for (int x = 0; x < W.width(); x++) {
//      wmove(stdscr, y, x);
    }
  }

  curs_set(true);
  wrefresh(stdscr);
}

int Renderer::get_input() {
  int ch = wgetch(stdscr);
  return ch;
}
