#include "common.h"
#include "curses.h"
#include "input_manager.h"
#include "sequence.h"
#include <cstdint>
#include <expected>
#include <fstream>
#include <memory>
#include <tuple>
#include <unordered_map>

class Vimktor {
  // methods
public:
  typedef std::unordered_map<std::string, VimktorEvent_t> CommandList_t;

  Vimktor() : m_window(stdscr), m_mode(NORMAL) {}
  Vimktor(WINDOW *window, std::fstream &file)
      : m_window(window), m_mode(NORMAL) {}

  void Init();
  void End();
  void Loop();
  // private:
  VimktorErr_t LoadFile(const std::string &fileName);

  VimktorErr_t WriteFile(const std::string &fileName);
  VimktorErr_t WriteFile();
  VimktorErr_t InitCurses();

  // renderer
  VimktorErr_t RenderLineNumber();
  VimktorErr_t RenderWindow();
  VimktorErr_t RenderHelper();
  void HelperLog(const std::string& msg);
  VimktorErr_t RenderCursor();
  VimktorErr_t RenderText(uint16_t x, uint16_t y, uint16_t width,
                          uint16_t height);
  position_t GetEditorDimensions();
  VimktorErr_t GetInput();

  VimktorErr_t HandleEvents(VimktorEvent_t event);
  VimktorErr_t HandleCommands();

  // variables
  WINDOW *m_window;
  Sequence m_sequence;
  VimktorMode_t m_mode;

private:
  static CommandList_t commandList;
  std::string m_filename;
};
