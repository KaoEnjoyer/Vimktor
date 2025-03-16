#include "window.h"
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ncurses.h>
#include <string>

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
  m_cursor = new Cursor(0, m_width, 0, m_height);
}

void Window::init_buffer() {
  m_buffer.resize(m_height);
  for (int i = 0; i < m_height; i++) {
    m_buffer[i].resize(m_width);
  }
  clear_buffer();
}

void Window::refresh() {

  m_status->update(m_cursor, m_textbox, m_mode);

  load_to_buffer();
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
  m_linenums->to_buffer(m_buffer, m_textbox->line());
  m_textbox->to_buffer(m_buffer);
  m_status->to_buffer(m_buffer);
}

Cursor::Cursor(int min_x, int max_x, int min_y, int max_y) {
  this->max_y = max_x;
  this->min_y = min_y;
  this->max_x = max_x;
  this->min_x = min_x;
  m_x = 0;
  m_y = 0;
}

Cursor::Cursor() {

  m_x = 0;
  m_y = 0;
}

Status::Status(size_t win_height, size_t win_width) {
  m_width = win_width;
  m_height = _STATUS_DEFAULT_HEIGHT;

  m_x = 0;
  m_y = win_height - _STATUS_DEFAULT_HEIGHT;
  top = "hej jestem top status";
  bot = "hej jestem bot status";
}

void Status::send_msg(const std::string &msg) { bot = msg; }

void Status::to_buffer(std::vector<std::vector<int>> &buff) {

  for (int x = m_x; x < m_width; x++) {
    if (x >= buff.size()) {
      return;
    }

    buff[m_y][x] = top[x - m_x];
    buff[m_y + 1][x] = bot[x - m_x];
  }
}

void Status::update(Cursor *c, Textbox *t, EditorMode ed) {

  top.resize(m_width);
  for(int i = 0 ; i < top.size(); i++)top[i] = ' ';
  std::string temp;
  temp = "line: " + std::to_string(c->x()) + " col: " + std::to_string(c->y());
  std::string temp2;

  // std::string temp = "line: " + std::to_string(c->x());
  // temp += " col: " + std::to_string(c->y());
  // top.clear();
  // top.resize(m_width);
  // top.replace(m_width - temp.size(), temp.size(), temp);

  // temp.clear();
  switch (ed) {
  case Visual:
    temp2 += "mode: Visual";
    break;
  case Normal:
    temp2 += "mode: Normal";
    break;
  case Input:
    temp2 += "mode: Input";
    break;
  default:
    temp2 += "mode: None";
    break;
  }
  temp2 += "     " + t->file_name();

  top.replace(0, temp2.size(), temp2);
  
  top.replace(temp2.size()+1, temp.size() + 5, temp); 

}

Textbox::Textbox(size_t win_height, size_t win_width) {
  m_x = _LINE_NUM_DEFAULT_WIDTH;
  m_y = 0;
  m_height = win_height - _STATUS_DEFAULT_HEIGHT;
  m_width = win_width - _LINE_NUM_DEFAULT_WIDTH;
  starting_line = 0;
  starting_coll = 0;

  m_file_name = "no file selected";
}

void Textbox::to_buffer(std::vector<std::vector<int>> &buff) const {
  size_t x_offset = column() + x();
  size_t y_offset = line() + y();

  size_t y = y_offset;
  for (auto &el : buff) {
    if (y >= data.size())
      return;
    if (y >= m_height)
      return;

    for (int x = x_offset; x < el.size(); x++) {
      if (x - x_offset >= (data[y]).size())
        el[x] = ' ';
      else
        el[x] = (data[y])[x - x_offset];
    }
    y++;
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

void Textbox::load_file(const std::string &file_name) {
  std::fstream file;
  file.open(file_name, std::fstream::in);

  std::string line;
  while (std::getline(file, line)) {
    data.push_back(line);
  }
  m_file_name = file_name;
  file.close();
}

Linenumbers::Linenumbers(size_t win_height, size_t win_width) {
  m_height = win_height - _STATUS_DEFAULT_HEIGHT;
  m_width = _LINE_NUM_DEFAULT_WIDTH;
  m_x = 0;
  m_y = 0;
  current_line = 0;
}

void Linenumbers::to_buffer(std::vector<std::vector<int>> &buff,
                            size_t line) const {
  for (int y = m_y; y < height(); y++) {
    std::string num = std::to_string(line + y);
    int offset = m_width - num.size() - 1;

    for (int i = offset; i < m_width - 1; i++) {
      buff[y][i] = num[i - offset];
    }
  }
}
