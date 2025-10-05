#pragma once
#include "common.h"
#include <cstdint>
#include <expected>
#include <fstream>
#include <string>
#include <vector>

// glyph_t covers a char type functionality but it also contains color
// field for all coloring featuers like LSP and code formating

#define GLYPH_COLOR_16BIT
#define GLYPH_CHAR_8BIT

size_t const DEFAULT_SEQUENCE_LINE_NUM = (1 << 9);
// how much lines does sequence reserve on init

typedef struct glyphStruct {
  int32_t ch;
  int32_t color;

  operator char() { return (char)ch; }
  inline glyphStruct(uint32_t ch) : ch(ch) {};
  inline glyphStruct() : ch('\0'), color(0x0000) {};
  // in fact the color is 24-bit
  // each 8 bits are another color scale
  // ncurses forces strange color range
  // where colors are defined by (x,y,z)
  // where 0<x,y,z <1000
} glyph_t;

/**
 * Sequence class is abstraction over character sequence edited by Vimtkor
 * in current implementation this abstraction is't really needed, but in futuer
 * this may be changed for now 2D vector of glyph_t is fast enaught
 *
 *
 * Sequence's methods like GetLineAt will give realative line to cursors page id
 * for eg. if m_cursor.pagePos.y = 33
 * GetLineAt(0) would return line nr. 33
 *
 * **/
class Sequence {
public:
  Sequence() = default;
  Sequence(std::fstream &file);

  VimktorErr_t LoadFile(std::fstream &file);

  inline const size_t Size() { return data.size(); }
  inline void Reserve(size_t n) { data.reserve(n); }

  std::expected<glyph_t *, VimktorErr_t> GetGlyphAt(size_t col, size_t line);
  std::expected<glyph_t *, VimktorErr_t>
  GetGlyphAtRel(size_t col,
                size_t line); // relative , you dont need to consider pageOffset
  void AddGlyphAt(size_t col, size_t line, glyph_t glyph);

  std::vector<glyph_t> &GetLineAt(size_t line);
  std::vector<glyph_t> &operator[](size_t line);

  std::string GetStringAt(size_t line);

  inline const size_t LineSize(size_t line) { return data.at(line).size(); }
  void AddLine(const std::string &str);
  void SetLineTo(size_t line, const std::string &str);

  void AddCharTo(const position_t &pos);

  void AddCharCursor(const position_t &pos);
  // cursor

  VimktorErr_t CursorMove(CursorDirection dir);
  VimktorErr_t CursorMovePos(const position_t &pos);
  VimktorErr_t CursorMovePos(const position_t &&pos);
  VimktorErr_t CursorChangeLine(CursorDirection dir);

  void ManageLastPos(position_t &backUp);
  inline const position_t &GetCursorPos() const noexcept { return m_cursorPos; }
  inline const position_t &GetRelativeCursorPos() noexcept {

    return (m_cursorPos - m_pagePos);
  }
  position_t m_cursorPos;
  position_t m_cursorPosPrev; // this determines how much cursors should be
                              // offested after changin line
  position_t m_pagePos;

private:
  VimktorErr_t CursorPosValid();
  std::vector<std::vector<glyph_t>> data;
};
