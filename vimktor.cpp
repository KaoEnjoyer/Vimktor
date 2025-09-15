
#include "include/vimktor.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <fstream>

void Vimktor::Init() {

  InitCurses();
  m_window = stdscr;
#ifdef DEBUG_MODE

  LoadFile("test.cs");
  m_logFile.open("log_file.txt", std::ios::out | std::ios::in);

#endif
}

void Vimktor::End() {
#ifdef DEBUG_MODE
  m_logFile.close();
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

VimktorErr_t Vimktor::RenderWindow(uint16_t startX, uint16_t startY) {
  uint16_t maxX, maxY;
  getmaxyx(m_window, maxY, maxX);

  if (maxY < startX || maxX < startY)
    return INVALID_ARRGUMENT;

  uint16_t height = maxY - startY;
  uint16_t width = maxX - startX;

  if (m_txt_offset_y > m_sequence.size())
    return MEMORY_ERROR;

  for (int i = 0; i < height; i++) {
    if (startY + i >= m_sequence.size()) {
      DebugLog("okej");
      break;
    }
    RenderLine(startY + i);
  }
  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::RenderLine(uint16_t y) {
  int col = m_sequence[y].size() - m_txt_offset_x;

  for (int i = 0; i < col; i++) {
    size_t x = m_txt_offset_x + i;
    move(y, x);
    waddch(m_window, m_sequence.getGlyphAt(y, x));
    DebugLog("ok");
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

  m_sequence = Sequence(file);
  return VIMKTOR_OK;
};

void Vimktor::Loop() {
  while (1) {
    char ch = getch();
    RenderWindow(0, 0);
    if (ch == 'q')
      break;
  }
}
// gc
// ctrl + W + d
#ifdef DEBUG_MODE
void Vimktor::DebugLog(const std::string &msg) {
  m_logFile << msg << " at: " << __FILE__ << " " << __LINE__ << std::endl;
}
#endif
