#include "renderer.h"
#include "window.h"
#include <cstdio>
#include <iostream>
#include <ncurses.h>

int main() {
  Renderer r;
  Window w;

  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");
  w.m_textbox->data.push_back("wwoooooooooo");

  FILE *bob;
  bob = fopen("textbox.txt", "w");
  for (auto el : w.m_textbox->data) {
    fprintf(bob, "%s\n", el.c_str());
  }
        fclose(bob);
  while (r.get_input() != 'q') {
    r.renderWindow(w);
    w.debug();
  }
}
