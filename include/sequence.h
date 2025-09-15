#include <cstdint>
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
  uint32_t ch;
  uint32_t color;

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
 * **/
class Sequence {
public:
  Sequence() = default;
  Sequence(std::fstream &file);

  inline const size_t size() { return data.size(); }
  inline void reserve(size_t n) { data.reserve(n); }

  glyph_t &getGlyphAt(size_t col, size_t row);
	void addGlyphAt(size_t col , size_t row , glyph_t glyph);

  std::vector<glyph_t> &getLineAt(size_t line);
  std::vector<glyph_t> &operator[](size_t line);


  std::string getStringAt(size_t line);

  void addLine(const std::string &str);
  void setLineTo(size_t line, const std::string &str);

private:
  std::vector<std::vector<glyph_t>> data;
};
