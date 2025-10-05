
#include "include/input_manager.h"
#include "include/common.h"

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
  switch (inputCh) { default: }
  return HandleEvents(event);
};
VimktorErr_t Vimktor::GetInputNormal() {

  char pressed = wgetch(m_window);
  VimktorEvent_t event = EV_NONE;
  switch (pressed) {
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
  }
  return HandleEvents(event);
};
