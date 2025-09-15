#include "common.h"
#include "curses.h"
#include "sequence.h"
#include <cstdint>
#include <expected>
#include <fstream>
class Vimktor {
  // methods
public:
  Vimktor()
      : m_window(stdscr), m_window_offset_x(0), m_window_offset_y(0),
        m_mode(NORMAL) {}

  void Init();
  void End();
  void Loop();
  // private:
  VimktorErr_t LoadFile(const std::string &fileName);
  VimktorErr_t InitCurses();
  VimktorErr_t RenderWindow(uint16_t x, uint16_t y);

  VimktorErr_t RenderLine(uint16_t y);

  // variables
  WINDOW *m_window;
  uint64_t m_window_offset_x;
  uint64_t m_window_offset_y;
  Sequence m_sequence;
  VimktorMode_t m_mode;

#ifdef DEBUG_MODE
  void DebugLog(const std::string &msg);
  std::fstream m_logFile;
#endif
};
