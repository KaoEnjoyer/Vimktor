#pragma once
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <ncurses.h>
#include <string>
#include <vector>

#define _LINE_NUM_DEFAULT_WIDTH 5
#define _STATUS_DEFAULT_HEIGHT 2

#define _ESCAPE_KEY 27

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

enum EditorMode {
  Input,
  Normal,
  Visual,
};

class Cursor {
public:
  Cursor();
  Cursor(int min_x, int max_x, int min_y, int max_y, int max_line);
  void move(CursorDirection dir);

  const inline int x() const { return m_x; }
  const inline int y() const { return m_y; }
  const inline int line() const { return m_line; }
  const inline int maxline() const { return max_line; }

  const inline int dx() const { return m_line + m_x; }

private:
  bool IsInWindowi();
  size_t m_line;
  size_t max_line;
  size_t min_x;
  size_t min_y;
  size_t max_x;
  size_t max_y;
  size_t m_x;
  size_t m_y;
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

  std::string file_name() const { return m_file_name; };
  std::vector<std::string> data;

  void to_buffer(std::vector<std::vector<int>> &buff) const;

  void load_file(const std::string &file_name);

  void load_vector(const std::vector<std::string> &txt);

  void change_coll(int delta);
  void change_line(int delta);

private:
  int m_x;
  int m_y;
  int m_height;
  int m_width;
  std::string m_file_name;

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

  void to_buffer(std::vector<std::vector<int>> &buff, size_t line) const;

private:
  size_t m_height;
  size_t m_x;
  size_t m_y;
  size_t m_width;
  size_t current_line;
};

class Status {
public:
  Status(size_t win_height, size_t win_width);

  const int height() const { return m_height; }
  const int width() const { return m_width; }
  const int x() const { return m_x; }
  const int y() const { return m_y; }

  std::string top;
  std::string bot;

  void update(Cursor *c, Textbox *t, EditorMode ed);
  void send_msg(const std::string &msg);
  void to_buffer(std::vector<std::vector<int>> &buff);

private:
  size_t m_x;
  size_t m_y;
  size_t m_width;
  size_t m_height;
};

class Window {

public:
  Window();
  Window(int x, int y, int width, int height);

  ~Window(); // TODO:delete all the pointers
  // getters
  inline const int height() const { return m_height; }
  inline const int width() const { return m_width; }
  inline const int x() const { return m_y; }
  inline const int y() const { return m_y; }
  inline const EditorMode mode() const { return m_mode; }

  void SetMode(EditorMode em);

  void debug();
  virtual void refresh();

  virtual void handleInput(char ch);
  // bufer is data that should be rendered
  std::vector<std::vector<int>> m_buffer;

  // WINDOW *m_win;
  Textbox *m_textbox;
  Cursor *m_cursor;
  Status *m_status;
  Linenumbers *m_linenums;

protected:
  int m_height;
  int m_width;
  int m_x;
  int m_y;

  EditorMode m_mode;
  void load_to_buffer(); // TODO:
  void load_status();
  void load_line_num();

  void basicInput(char ch);
  void clear_buffer();
  void init_sub_sys();

  void init_buffer();

  void init_curses();
  void init_curses(int x, int y, int width, int height);
};
