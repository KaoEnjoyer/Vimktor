
#include "include/vimktor.h"
#include "include/common.h"
#include "include/sequence.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <curses.h>
#include <cwchar>
#include <fstream>
#include <memory>

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
  curs_set(1);
  init_color(COLOR, 0, 0, 0);
  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::RenderWindow() {
  uint16_t maxX, maxY;
  getmaxyx(m_window, maxY, maxX);

  if (maxX == 0 || maxY == 0)
    return MEMORY_ERROR;

  RenderText(0, 0, maxX, maxY);
  RenderCursor();
  wrefresh(m_window);
  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::RenderCursor() {
  wmove(m_window, m_cursorPos.y, m_cursorPos.x);

  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::RenderText(uint16_t x, uint16_t y, uint16_t width,
                                 uint16_t height) {

  position_t pageOffset = m_pagePos;
  for (uint16_t i_y = y; i_y < height; i_y++) {
    for (uint16_t i_x = x; i_x < width; i_x++) {

      glyph_t current =
          m_sequence->GetGlyphAt(i_x + pageOffset.x, i_y + pageOffset.y);
      wmove(m_window, i_y, i_x);
      if (current != '\0') {
        waddch(m_window, current);
      } else {
        waddch(m_window, ' ');
      }
    }
  }
  // TODO: add colors

  return VIMKTOR_OK;
}
VimktorErr_t Vimktor::GetInput() {
  char pressed = wgetch(m_window);
  VimktorEvent event = EVENT_NONE;
  switch (pressed) {
  case 'q':
    event = EVENT_CLOSE;
    break;
  case 'h':
    event = CURSOR_LEFT;
    break;
  case 'j':
    event = CURSOR_DOWN;
    break;
  case 'k':
    event = CURSOR_UP;
    break;
  case 'l':
    event = CURSOR_RIGHT;
    break;
  }
  return HandleEvents(event);
}

VimktorErr_t Vimktor::HandleEvents(VimktorEvent event) {
  VimktorErr_t err = VIMKTOR_OK;
  switch (event) {
  case CURSOR_DOWN:
    err = CursorMove(DOWN);
    break;
  case CURSOR_UP:
    CursorMove(UP);
    break;
  case CURSOR_RIGHT:
    CursorMove(RIGHT);
    break;
  case CURSOR_LEFT:
    CursorMove(LEFT);
    break;
  }
  return VIMKTOR_OK;
}

VimktorErr_t Vimktor::LoadFile(const std::string &fileName) {
  std::fstream file;
  file.open(fileName, std::ios::in);
  if (!file.good()) {
    return FILE_ERROR;
  }
  m_sequence->LoadFile(file);
  return VIMKTOR_OK;
};

void Vimktor::Loop() {
  while (1) {
    RenderWindow();
    GetInput();
  }
}
// gc
// ctrl + W + d
#ifdef DEBUG_MODE
void Vimktor::DebugLog(const std::string &msg) {
  m_logFile << msg << " at: " << __FILE__ << " " << __LINE__ << std::endl;
}
#endif

VimktorErr_t Vimktor::CursorMove(CursorDirection dir) noexcept {

  position_t backUp = m_cursorPos;
  if (dir == UP) {
    m_cursorPos.y--;
  } else if (dir == DOWN) {

    m_cursorPos.y++;
  } else if (dir == LEFT) {
    m_cursorPos.x--;
  } else if (dir == RIGHT) {
    m_cursorPos.x++;
  }
  // if (!IsPosValid()) {
  //   cursorPos = backUp;
  // } else {
  //   cursorPosPrev = backUp;
  // }
  return VIMKTOR_OK;
}
