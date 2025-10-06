#include "common.h"
#include "curses.h"
#include "input_manager.h"
#include "sequence.h"
#include <cstdint>
#include <expected>
#include <fstream>
#include <memory>
class Vimktor {
  // methods
public:
  Vimktor() : m_window(stdscr), m_mode(NORMAL) {}
  Vimktor(WINDOW *window, std::fstream &file)
      : m_window(window), m_mode(NORMAL) {}

  void Init();
  void End();
  void Loop();
  // private:
  VimktorErr_t LoadFile(const std::string &fileName);
  VimktorErr_t InitCurses();

  VimktorErr_t RenderWindow();

  VimktorErr_t RenderCursor();
  VimktorErr_t RenderText(uint16_t x, uint16_t y, uint16_t width,
                          uint16_t height);

  VimktorErr_t GetInput();
  VimktorErr_t HandleEvents(VimktorEvent_t event);
  // variables
  WINDOW *m_window;
  Sequence m_sequence;
  VimktorMode_t m_mode;

private:
};
