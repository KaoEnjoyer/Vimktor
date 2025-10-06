#include "include/sequence.h"
#include "include/common.h"
#include "include/vimktor_debug.h"
#include "vimktor_debug.cpp"
#include <assert.h>
#include <cstdio>
#include <expected>
#include <format>
#include <fstream>
#include <iostream>
Sequence::Sequence(std::fstream &file) { LoadFile(file); }

std::vector<glyph_t> &Sequence::operator[](size_t line) {
  assert(line < data.size());
  return (data[line]);
}

std::vector<glyph_t> &Sequence::GetLineAt(size_t line) {
  assert(line < data.size());
  return (data[line]);
}

std::expected<glyph_t *, VimktorErr_t> Sequence::GetGlyphAt(size_t col,
                                                            size_t line) {

  if (line >= data.size() || col >= data[line].size()) {
    return std::unexpected(INVALID_ARRGUMENT);
  }

  return &data[line][col];
}

std::expected<glyph_t *, VimktorErr_t> Sequence::GetGlyphAtRel(size_t col,
                                                               size_t line) {

  col = col + m_pagePos.x;
  line = line + m_pagePos.y;
  if (line >= data.size() || col >= data[line].size()) {
    return std::unexpected(INVALID_ARRGUMENT);
  }

  return &data[line][col];
}
void Sequence::SetLineTo(size_t line, const std::string &str) {
  assert(data.size() < line);

  if (str.size() > data[line].size()) {
    data[line].clear();
  }

  data[line].resize(0);
  for (auto el : str) {
    data[line].push_back(glyph_t(el));
  }
}

std::string Sequence::GetStringAt(size_t line) {

  assert(data.size() > line);

  std::string ans;
  ans.resize(data[line].size());

  size_t num = 0;
  for (auto glyph : data[line]) {
    ans[num++] = glyph;
  }
  return ans;
}

void Sequence::AddLine(const std::string &str) {
  auto &line_vec = data.emplace_back();
  for (auto ch : str) {
    line_vec.push_back(ch);
  }
}

VimktorErr_t Sequence::CursorMove(CursorDirection dir) {

  position_t backUp = m_cursorPos;

  if (dir == UP) {
    m_cursorPos.y--;
    // CursorChangeLine(UP);
  } else if (dir == DOWN) {
    m_cursorPos.y++;
    // CursorChangeLine(DOWN);
  } else if (dir == LEFT) {
    m_cursorPos.x--;
  } else if (dir == RIGHT) {
    m_cursorPos.x++;
  }

  ManageLastPos(backUp);
  return VIMKTOR_OK;
}

VimktorErr_t Sequence::CursorMovePos(const position_t &pos) {

  position_t backUp = m_cursorPos;
  m_cursorPos.x = pos.x;
  m_cursorPos.y = pos.y;
  ManageLastPos(backUp);
  return VIMKTOR_OK;
}

VimktorErr_t Sequence::CursorMovePos(const position_t &&pos) {

  position_t backUp = m_cursorPos;
  m_cursorPos.x = pos.x;
  m_cursorPos.y = pos.y;
  ManageLastPos(backUp);
  return VIMKTOR_OK;
}
void Sequence::ManageLastPos(position_t &backUp) {

  // this method fixes cursor positon after moving event
  //
  // make sure line exist
  //
  //

  if (m_cursorPos.x < 0) {
    m_cursorPos.x = 0;
    backUp.x = m_cursorPos.x;
  }

  if (m_cursorPos.y < 0) {
    m_cursorPos.y = 0;
    backUp.y = m_cursorPos.y;
  }
  if (m_cursorPos.y >= Size() && m_cursorPos.y != 0) {
    m_cursorPos.y = Size() - 1;
  }

  if (m_cursorPos.x != backUp.x) {
    // jezeli jestesmy w tej samej lini

    if (m_cursorPos.x >= LineSize(m_cursorPos.y) && m_cursorPos.x != 0) {
      m_cursorPos.x = LineSize(m_cursorPos.y) - 1;
    }
    m_cursorPosPrev.x = m_cursorPos.x;
  } else {
    m_cursorPos.x = m_cursorPosPrev.x;
  }
  if (m_cursorPos.x >= LineSize(m_cursorPos.y) && m_cursorPos.x != 0) {
    m_cursorPos.x = LineSize(m_cursorPos.y) - 1;
    if (m_cursorPos.x < 0)
      m_cursorPos.x = 0;
  }

  return;
}

VimktorErr_t Sequence::CursorChangeLine(CursorDirection dir) {
  if (dir != UP && dir != DOWN)
    return VimktorErr_t::INVALID_ARRGUMENT;
  if (dir == UP)
    m_cursorPos.y--;
  if (dir == DOWN)
    m_cursorPos.y++;

  if (CursorPosValid() != VIMKTOR_OK)
    return VimktorErr_t::EOL_ERROR;

  if (m_cursorPosPrev.x >= LineSize(m_cursorPos.y)) {
    if (LineSize(m_cursorPos.y) == 0)
      m_cursorPos.x = 0;
    m_cursorPos.x = LineSize(m_cursorPos.y) - 1;

  } else {
    m_cursorPos.x = m_cursorPosPrev.x;
  }
  return VIMKTOR_OK;
}

void Sequence::AddGlyphAt(size_t col, size_t line, glyph_t glyph) {
  auto &buffer = GetLineAt(line);

  buffer.insert(buffer.begin() + col, glyph);
}

VimktorErr_t Sequence::LoadFile(std::fstream &file) {

  data.reserve(DEFAULT_SEQUENCE_LINE_NUM);

  std::string line;

  while (!file.eof()) {
    getline(file, line);
    auto &element = data.emplace_back(std::vector<glyph_t>());
    element.reserve(line.size());

    for (char ch : line) {
      element.emplace_back(glyph_t(ch));
    }
  }
  return VIMKTOR_OK;
}

VimktorErr_t Sequence::CursorPosValid() {
  if (m_cursorPos.x < 0 || m_cursorPos.y < 0)
    return MEMORY_ERROR;
  if (m_cursorPos.y > Size()) {
    return MEMORY_ERROR;
  }
  if (m_cursorPos.x == 0)
    return VIMKTOR_OK;
  if (m_cursorPos.x >= LineSize(m_cursorPos.y)) {
    return MEMORY_ERROR;
  }
  return VIMKTOR_OK;
}

void Sequence::InsertCharCursor(const glyph_t &gl) {
  const auto itr = data[m_cursorPos.y].begin() + m_cursorPos.x;
  data[m_cursorPos.y].insert(itr, gl);
  CursorMove(RIGHT);
}

void Sequence::EraseCharCursor() {
  const auto itr = data[m_cursorPos.y].begin() + m_cursorPos.x;

  if (m_cursorPos.x == 0) {
    EraseLineCursor();
    CursorMove(UP);
    CursorMoveEol();
    return;
  }
  data[m_cursorPos.y].erase(itr);
  CursorMove(LEFT);
}

void Sequence::EraseLineCursor() {
  const auto itr = data.begin() + m_cursorPos.y;
  data.erase(itr);
};

VimktorErr_t Sequence::CursorMoveEol() {
  auto backUp = m_cursorPos;
  m_cursorPos.x = LineSize(m_cursorPos.y) - 1;
  ManageLastPos(backUp);
  return VIMKTOR_OK;
}
