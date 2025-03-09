#pragma once
#include <ncurses.h>
#include "window.h"

class Renderer {
  public: 
  ~Renderer();
  Renderer();
  int get_input();
  void renderWindow(Window & W);
  private:
//  void renderStatus()
};
