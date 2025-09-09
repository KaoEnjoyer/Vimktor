#include "vimktor.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <fstream>

void Vimktor::Init() {

  InitCurses();
  window = stdscr;
#ifdef DEBUG_MODE
  LoadFile("test.cs");
  logFile.open("log_file.txt", std::ios::out);
#endif
}

void Vimktor::End() {
#ifdef DEBUG_MODE
  logFile.close();
#endif

  endwin();
}

VimktorErr_t Vimktor::InitCurses() {
  initscr();
  keypad(stdscr, true);
  raw();
  nodelay(stdscr, true);
  noecho();
  init_color(COLOR, 0, 0, 0);
  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::RenderWindow(WINDOW *window, uint16_t x, uint16_t y,
                                   textBuffer &tb) {
  uint16_t maxX, maxY;
  getmaxyx(window, maxY, maxX);

  if (maxY < y || maxX < x)
    return INVALID_ARRGUMENT;

  uint16_t height = maxY - y;
  uint16_t width = maxX - x;

  if (txt_offset_y > tb.size())
    return MEMORY_ERROR;

  for (int i = 0; i < height; i++) {
    RenderLine(window, x, y + i, tb[txt_offset_y + i]);
  }
  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::RenderLine(WINDOW *window, uint16_t x, uint16_t y,
                                 const std::vector<glyph_t> &buff) {
  int col = buff.size() - txt_offset_x;

  for (int i = 0; i < col; i++) {
    move(y, txt_offset_x + i);
    waddch(window, buff[txt_offset_x + i].ch);

    // TODO: add colors
  }

  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::LoadFile(const std::string &fileName) {
  std::fstream file;
  file.open(fileName, std::ios::in);
  if (!file.good()) {
    return FILE_ERROR;
  }

  tb.clear();
  tb.reserve(1000);
  size_t line_num = 0;
  std::string line;
  while (file >> line) {
    tb.push_back(std::vector<glyph_t>());

    for (int i = 0; i < line.size(); i++) {

      glyph_t g;
      g.ch = line[i];
      tb[line_num].push_back(g);
    }

    line_num++;
  }

  return VIMKTOR_OK;
};

void Vimktor::Loop() {
  while (1) {
    char ch = getch();
    RenderWindow(window, 0, 0, tb);
    if (ch == 'q')
      break;
  }
}
