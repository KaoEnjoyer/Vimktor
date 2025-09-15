#include "include/sequence.h"
#include <assert.h>
#include <cstdio>
#include <fstream>
#include <iostream>
Sequence::Sequence(std::fstream &file) {

  data.reserve(DEFAULT_SEQUENCE_LINE_NUM);

  std::string line;

  while (!file.eof()) {
    getline(file, line);
    auto &element = data.emplace_back(std::vector<glyph_t>());
    element.reserve(line.size());

    for (char ch : line) {
      element.emplace_back(glyph_t(ch));
    }
  }
}

std::vector<glyph_t> &Sequence::operator[](size_t line) {
  assert(line < data.size());
  return (data[line]);
}

std::vector<glyph_t> &Sequence::getLineAt(size_t line) {
  assert(line < data.size());
  return (data[line]);
}

void Sequence::setLineTo(size_t line, const std::string &str) {
  assert(data.size() < line);

  if (str.size() > data[line].size()) {
    data[line].clear();
  }

  data[line].resize(0);
  for (auto el : str) {
    data[line].push_back(glyph_t(el));
  }
}

std::string Sequence::getStringAt(size_t line) {

  assert(data.size() > line);

  std::string ans;
  ans.resize(data[line].size());

  size_t num = 0;
  for (auto glyph : data[line]) {
    ans[num++] = glyph;
  }
  return ans;
}

void Sequence::addLine(const std::string &str) {
  auto &line_vec = data.emplace_back();
  for (auto ch : str) {
    line_vec.push_back(ch);
  }
}

void Sequence::addGlyphAt(size_t col, size_t row, glyph_t glyph) {
  auto &line = getLineAt(row);
  line.insert(line.begin() + row, glyph);
}
