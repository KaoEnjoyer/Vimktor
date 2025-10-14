
#include "include/input_manager.h"
#include "include/common.h"
#include "include/vimktor_debug.h"
#include <format>
#include <ncurses.h>

VimktorEvent_t InputManager::GetEvent(WINDOW *win, VimktorMode_t mode) {
  inputCh = wgetch(win);
  if (inputCh == -1)
    return EV_NONE;
  nodelay(win, false);
  if (inputCh == 0xffffffff)
    return EV_NONE;
  switch (mode) {
  case VimktorMode_t::NORMAL:
    return GetInputNormal(win);
    break;
  case VimktorMode_t::INSERT:
    return GetInputInsert(win);
    break;
  default:
    return VimktorEvent_t::EV_NONE;
    break;
  }

  nodelay(win, true);
}

VimktorEvent_t InputManager::GetInputInsert(WINDOW *win) {

  VimktorEvent_t event = EV_NONE;
  event = IsEscapePressed();
  if (event != EV_NONE)
    return event;
  switch (inputCh) {
  case 'q':
    return EV_CLOSE;
    break;
  case KEY_UP:
    return EV_CURSOR_UP;
    break;
  case KEY_DOWN:
    return EV_CURSOR_DOWN;
    break;
  case KEY_LEFT:
    return EV_CURSOR_LEFT;
    break;
  case KEY_RIGHT:
    return EV_CURSOR_RIGHT;
    break;
  case KEY_BACKSPACE:
    return EV_BACKSPACE;
    break;
  case 0:
    break;
  default:
    return EV_INSERT_TEXT;
    break;
  }
};

VimktorEvent_t InputManager::GetInputNormal(WINDOW *win) {

  VimktorEvent_t event = EV_NONE;
  switch (inputCh) {
  case KEY_UP:
    return EV_CURSOR_UP;
    break;
  case KEY_DOWN:
    return EV_CURSOR_DOWN;
    break;
  case KEY_LEFT:
    return EV_CURSOR_LEFT;
    break;
  case KEY_RIGHT:
    return EV_CURSOR_RIGHT;
    break;
  case 'q':
    event = EV_CLOSE;
    break;
  case 'h':
    event = EV_CURSOR_LEFT;
    break;
  case 'j':
    event = EV_CURSOR_DOWN;
    break;
  case 'k':
    event = EV_CURSOR_UP;
    break;
  case 'l':
    event = EV_CURSOR_RIGHT;
    break;
  case '$':
    event = EV_GO_TO_EOL;
    break;
  case '0':
    event = EV_GO_TO_SOL;
    break;
  case 'i':
    event = EV_MODE_INSERT;
    break;
  case 'd':
    return HandleDeleteEvent(win);
    break;
  case 'a':
    event = EV_MODE_INSERT_RIGHT;
    break;
  default:
    event = EV_NONE;
    break;
  }
  return event;
};

VimktorEvent_t InputManager::IsEscapePressed() {
  if (inputCh == KEY_ESCAPE) {
    nodelay(stdscr, 1);
    char n = getch();
    // if (n == 0)
    return EV_MODE_NORMAL;
  }
  return EV_NONE;
}

VimktorEvent_t InputManager::HandleDeleteEvent(WINDOW *win) {

  uint16_t nextOp = wgetch(win);

  switch (nextOp) {
  case 'd':
    return EV_ERASE_LINE;
    break;
  default:
    if (IsEscapePressed() != EV_NONE)
      return EV_NONE;
  }
  return EV_NONE;
}
