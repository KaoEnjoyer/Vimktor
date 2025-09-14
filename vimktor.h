#include "curses.h"
#include "sequence.h"
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
  // methods
public:
  Vimktor() : m_window(stdscr), m_txt_offset_x(0), m_txt_offset_y(0) {}
  void Init();
  void End();
  void Loop();
  // private:
  VimktorErr_t LoadFile(const std::string &fileName);
  VimktorErr_t InitCurses();
  VimktorErr_t RenderWindow(WINDOW *window, uint16_t x, uint16_t y);

  VimktorErr_t RenderLine(WINDOW *window, uint16_t x, uint16_t y);

  // variables

  WINDOW *m_window;
  uint64_t m_txt_offset_y;
  uint64_t m_txt_offset_x;
  Sequence m_sequence;

#ifdef DEBUG_MODE
  void DebugLog(const std::string &msg);
  std::fstream logFile;
#endif
};
