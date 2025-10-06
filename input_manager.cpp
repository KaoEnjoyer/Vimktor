
#include "include/input_manager.h"
#include "include/common.h"
#include <ncurses.h>

VimktorEvent_t InputManager::GetEvent(WINDOW *win, VimktorMode_t mode) {

  inputCh = wgetch(win);

 switch (mode) {
  case VimktorMode_t::NORMAL:
    return GetInputNormal();
    break;
  case VimktorMode_t::INSERT:
    return GetInputInsert();
    break;
  default:
    return VimktorEvent_t::EV_NONE;
    break;
  }
}

VimktorEvent_t InputManager::GetInputInsert() {

  VimktorEvent_t event = EV_NONE;
  event = IsEscapePressed();
  if (event != EV_NONE)
    return event;

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

  default:
    return EV_INSERT_TEXT;
    break;
  }
};

VimktorEvent_t InputManager::GetInputNormal() {

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
  case 'i':
    event = EV_MODE_INSERT;
    break;
  default:
    event = EV_NONE;
    break;
  }
  return event;
};

VimktorEvent_t InputManager::IsEscapePressed() {
  if (inputCh == KEY_ESCAPE) {
    char n = getch();
    if (n == 0)
      return EV_MODE_NORMAL;
  }
  return EV_NONE;
}
