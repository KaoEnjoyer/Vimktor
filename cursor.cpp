#include "include/cursor.h"
#include "include/common.h"
#include <expected>
#include <utility>

VimktorErr_t Cursor::Move(CursorDirection direction) {
  position_t backUp = cursorPos;
  if (direction == UP) {
    cursorPos.y--;
  } else if (direction == DOWN) {
    cursorPos.y++;
  } else if (direction == LEFT) {
    cursorPos.x--;
  } else if (direction == RIGHT) {
    cursorPos.x++;
  }
  if (!IsPosValid()) {
    cursorPos = backUp;
  } else {
    cursorPosPrev = backUp;
  }
  return VIMKTOR_OK;
}

bool Cursor::IsPosValid() {
  return (m_sequence->Size() >= cursorPos.y) &&
         ((*m_sequence)[cursorPos.y].size() >= cursorPos.x);
}
