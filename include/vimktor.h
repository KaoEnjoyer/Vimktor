#include "common.h"
#include "curses.h"
#include "cursor.h"
#include "sequence.h"
#include <cstdint>
#include <expected>
#include <fstream>
#include <memory>

class Vimktor {
  // methods
public:
  Vimktor() : m_window(stdscr), m_mode(NORMAL) {
    m_sequence = std::make_unique<Sequence>();
  }
  Vimktor(WINDOW *window, std::fstream &file)
      : m_window(window), m_mode(NORMAL) {
    m_sequence = std::make_unique<Sequence>(file);
  }

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
  VimktorErr_t HandleEvents(VimktorEvent event);
  // cursor
  position_t m_cursorPos;
  position_t m_pagePos;
	//TODO :
  VimktorErr_t CursorMove(CursorDirection dir) noexcept;
  // variables
  WINDOW *m_window;
  std::unique_ptr<Sequence> m_sequence;
  VimktorMode_t m_mode;
#ifdef DEBUG_MODE
  void DebugLog(const std::string &msg);
  std::fstream m_logFile;
#endif
};
