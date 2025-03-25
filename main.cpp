#include "renderer.h"
#include "window.h"
#include <cstdio>
#include <iostream>
#include <ncurses.h>
#include "filemanager.h"

int main() {
  Renderer r;
 // Window w;
  FileManager w;


  w.m_status->send_msg("PROSZE DZIALAJ");

  char ch;
  while (ch != 'q') {
    ch = r.get_input();
    w.refresh();
    r.renderWindow(w);
    w.debug();
    w.handleInput(ch);
  }
  FILE *bob;
  bob = fopen("textbox.txt", "w");
  for (auto el : w.m_textbox->data) {
    fprintf(bob, "%s\n", w.m_status->top.c_str());
  }
        fclose(bob);
}
