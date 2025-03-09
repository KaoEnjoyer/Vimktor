#include "window.h"
#include <cstdio>
#include <ncurses.h>

Window::Window() {
  init_curses();
  m_height = LINES;
  m_width = COLS;
  m_x = 0;
  m_y = 0;
  init_buffer();
  init_sub_sys();
};

Window::Window(int x, int y, int width, int height) {
  init_curses(x, y, width, height);
  m_x = x;
  m_y = y;
  m_width = width;
  m_height = height;
  // TODO: init_sub_sys for special params
  init_sub_sys();
}

Window::~Window() {
  //  delete m_cursor;
  //  delete m_linenums;
  //  delete m_textbox;
  //  delete m_status;
}

void Window::init_curses(int x, int y, int width, int height) {
  //  m_win = newwin(height, width, y, x);
  //  keypad(m_win, 1);
}
void Window::init_curses() {
  //  m_win = newwin(0, 0, 0, 0);
  //  keypad(m_win, 1);
}

void Window::init_sub_sys() {
  m_linenums = new Linenumbers(m_height, m_width);
  m_status = new Status(m_height, m_width);
  m_textbox = new Textbox(m_height, m_width);
}

void Window::init_buffer() {
  m_buffer.resize(m_height);
  for (int i = 0; i < m_height; i++) {
    m_buffer[i].resize(m_width);
  }
  clear_buffer();
}

void Window::clear_buffer() {
  for (auto &el : m_buffer) {
    for (int i = 0; i < el.size(); i++) {
      el[i] = ' ';
    }
  }
}

void Window::debug() {
  FILE *output;
  output = fopen("window.txt", "w");
  auto s = this->m_status;
  fprintf(output, "Status x: %d, y: %d, h: %d, w%d \n", s->x(), s->y(),
          s->height(), s->width());

  auto t = this->m_textbox;

  fprintf(output, "Text x: %d, y: %d, h: %d, w%d \n", t->x(), t->y(),
          t->height(), t->width());

  fprintf(output, "Win x: %d, y: %d, h: %d, w%d \n", this->x(), this->y(),
          this->height(), this->width());

  fclose(output);
}

void Window::load_to_buffer() {
  m_textbox->to_buffer(m_buffer);
}

Cursor::Cursor(int min_x, int max_x, int min_y, int max_y) {
  this->max_y = max_x;
  this->min_y = min_y;
  this->max_x = max_x;
  this->min_x = min_x;
}

Cursor::Cursor() {}

Status::Status(size_t win_height, size_t win_width) {
  m_width = win_width;
  m_height = _STATUS_DEFAULT_HEIGHT;

  m_x = 0;
  m_y = win_height - _STATUS_DEFAULT_HEIGHT;
  top = "hej jestem top status";
  bot = "hej jestem bot status";
}

Textbox::Textbox(size_t win_height, size_t win_width) {
  m_x = _LINE_NUM_DEFAULT_WIDTH;
  m_y = 0;
  m_height = win_height - _STATUS_DEFAULT_HEIGHT;
  m_width = win_width - _LINE_NUM_DEFAULT_WIDTH;
  starting_line = 0;
  starting_coll = 0;
}

void Textbox::to_buffer(std::vector<std::vector<int>> &buff) const {
   
  auto data_itr = data.begin();
  for (auto &el : buff) {
    if (data_itr == data.end())
      return;

    for (int x = line(); x < el.size(); x++) {
      if (x - line() >= (*data_itr).size())
        el[x] = ' ';
      else
        el[x] = (*data_itr)[x - line()];
    }
    data_itr++;
  }
}

void Textbox::change_coll(int delta) {
  int tmp = starting_coll + delta;
  if (tmp < 0) {
    starting_line = 0;
    return;
  }
  if (tmp >= data.size()) {
    starting_coll = data.size();
    return;
  }
  starting_coll = tmp;
}
void Textbox::change_line(int delta) {
  int tmp = starting_line + delta;
  if (tmp < 0) {
    starting_line = 0;
    return;
  }
  if (tmp >= data.size()) {
    starting_line = data.size();
    return;
  }
  starting_line = tmp;
}

Linenumbers::Linenumbers(size_t win_height, size_t win_width) {
  m_height = win_height - _STATUS_DEFAULT_HEIGHT;
  m_width = _LINE_NUM_DEFAULT_WIDTH;
  m_x = 0;
  m_y = 0;
  current_line = 0;
}
