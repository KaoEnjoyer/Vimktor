#pragma once
#include "common.h"
#include "inttypes.h"
#include "sequence.h"
#include <cstdint>
#include <expected>
#include <memory>
class Cursor {
public:
  Cursor()
      : cursorPos(position_t(0, 0)), pagePos(position_t(0, 0)),
        cursorPosPrev(cursorPos) {}
  Cursor(uint32_t pos_x, uint32_t pos_y, uint32_t page_x, uint32_t page_y)
      : cursorPos(position_t(pos_x, pos_y)),
        pagePos(position_t(page_x, page_y)), cursorPosPrev(cursorPos) {}

  VimktorErr_t Move(CursorDirection direction);

  void SetSequence(Sequence *ptr) { m_sequence = ptr; }
  inline const position_t &GetCursorPos() const { return cursorPos; }
  inline const position_t &GetPagePos() const { return pagePos; }

private:
  bool IsPosValid();
  position_t cursorPos;
  position_t cursorPosPrev;

  Sequence *m_sequence;

  // cursor positon is struct with coordinates of place in Sequence that is
  // currently edited just like an cursor in any other editor
  position_t pagePos;
  // page position is place where rendered on window text starts
  // for example if pagePos.y == 3
  // in the left-top corner of window line nr 4 would be printed
};
