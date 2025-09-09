#include "curses.h"
#include "textbuffer.h"
#include <cstdint>
#include <expected>
#include <fstream>
#define DEBUG_MODE 1

enum VimktorErr_t {
  VIMKTOR_OK,
  MEMORY_ERROR,
  INVALID_ARRGUMENT,
  NULLEXCEPT,
  FILE_ERROR,
};

#define COLOR 1

class Vimktor {
public:
  Vimktor() : window(stdscr), txt_offset_x(0), txt_offset_y(0) {}
  void Init();
  void End();
  void Loop();
  // private:
  VimktorErr_t LoadFile(const std::string &fileName);
  VimktorErr_t InitCurses();
  VimktorErr_t RenderWindow(WINDOW *window, uint16_t x, uint16_t y,
                            textBuffer &tb);

  VimktorErr_t RenderLine(WINDOW *window, uint16_t x, uint16_t y,
                          const std::vector<glyph_t> &buff);
  WINDOW *window;
  uint64_t txt_offset_y;
  uint64_t txt_offset_x;
  textBuffer tb;
#ifdef DEBUG_MODE
  void DebugLog(const std::string &msg);
  std::fstream logFile;
#endif
};
