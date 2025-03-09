#pragma once
#include <cstddef>
#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <vector>

#define _LINE_NUM_DEFAULT_WIDTH 5
#define _STATUS_DEFAULT_HEIGHT 2

//          BUFFER:
// ----------------------------------------
// |l|                                    |
// |i|                                    |
// |n|                                    |
// |e|                                    |
// | |                                    |
// |n|             TextBox                |
// |u|                                    |
// |m|                                    |
// |--------------------------------------|
// |status                                |
// |                                      |
// ----------------------------------------
//

enum CursorDirection {
  Up,
  Down,
  Left,
  Right,
};

class Cursor {
public:
  Cursor();
  Cursor(int min_x, int max_x, int min_y, int max_y);
  void move(CursorDirection dir);

  const int x() const { return m_y; }
  const int y() const { return m_y; }

private:
  bool IsInWindow();
  size_t min_x;
  size_t min_y;
  size_t max_x;
  size_t max_y;
  size_t m_x;
  size_t m_y;
};

class Status {
public:
  Status(size_t win_height, size_t win_width);

  const int height() const { return m_height; }
  const int width() const { return m_width; }
  const int x() const { return m_y; }
  const int y() const { return m_y; }

private:
  size_t m_x;
  size_t m_y;
  size_t m_width;
  size_t m_height;
  std::string top;
  std::string bot;
};

class Textbox {
public:
  Textbox(size_t win_height, size_t win_width);
  // relative to window
  int height() const { return m_height; }
  int width() const { return m_width; }
  int x() const { return m_x; }
  int y() const { return m_y; }
  int line() const { return starting_line; }
  int column() const { return starting_coll; }

  std::vector<std::string> data;

  void to_buffer(std::vector<std::vector<int>> &buff) const;

  void change_coll(int delta);
  void change_line(int delta);

private:
  int m_x;
  int m_y;
  int m_height;
  int m_width;
  size_t starting_line;
  size_t starting_coll;
  // all the data
  // text box is structure that shrink data to buffer in the right place
};

class Linenumbers {
public:
  Linenumbers(size_t win_height, size_t win_width);
  bool is_relative;

  // returns line on top of the window
  const int line() const { return current_line; }

  const int height() const { return m_height; }
  const int width() const { return m_width; }
  const int x() const { return m_y; }
  const int y() const { return m_y; }

private:
  size_t m_height;
  size_t m_x;
  size_t m_y;
  size_t m_width;
  size_t current_line;
};

class Window {

public:
  Window();
  Window(int x, int y, int width, int height);

  ~Window(); // TODO:delete all the pointers
  // getters
  const int height() const { return m_height; }
  const int width() const { return m_width; }
  const int x() const { return m_y; }
  const int y() const { return m_y; }

  void clear_buffer();
  void debug();

  // bufer is data that should be rendered
  std::vector<std::vector<int>> m_buffer;

  // WINDOW *m_win;
  Textbox *m_textbox;
  Cursor *m_cursor;
  Status *m_status;
  Linenumbers *m_linenums;

private:
  int m_height;
  int m_width;
  int m_x;
  int m_y;
  void load_to_buffer(); // TODO:
  void load_status();
  void load_line_num();

  void init_sub_sys();

  void init_buffer();

  void init_curses();
  void init_curses(int x, int y, int width, int height);
};
