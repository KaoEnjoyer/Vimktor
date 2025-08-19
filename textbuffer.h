#include <string>
#include <vector>

// glyph_t covers a char type functionality but it also contains color
// field for all coloring featuers like LSP and code formating

#define GLYPH_COLOR_16BIT
#define GLYPH_CHAR_8BIT

typedef struct glyphStruct glyph_t;

typedef std::vector<std::vector<glyph_t>> textBuffer;

struct glyphStruct {
  uint32_t ch;
  uint32_t color; 
	// in fact the color is 24-bit 
	// each 8 bits are another color scale 
	// ncurses forces strange color range
	// where colors are defined by (x,y,z)
	// where 0<x,y,z <1000
};
