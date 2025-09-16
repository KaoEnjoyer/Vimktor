#include "include/sequence.h"
#include "include/common.h"
#include <assert.h>
#include <cstdio>
#include <expected>
#include <fstream>
#include <iostream>
Sequence::Sequence(std::fstream &file) { LoadFile(file); }

std::vector<glyph_t> &Sequence::operator[](size_t line) {
  assert(line < data.size());
  return (data[line]);
}

std::vector<glyph_t> &Sequence::GetLineAt(size_t line) {
  assert(line < data.size());
  return (data[line]);
}

glyph_t Sequence::GetGlyphAt(size_t col, size_t line) {
  assert(line < data.size());

  if (col >= data[line].size())
    return glyph_t('\0');
  return data[line][col];
}

void Sequence::SetLineTo(size_t line, const std::string &str) {
  assert(data.size() < line);

  if (str.size() > data[line].size()) {
    data[line].clear();
  }

  data[line].resize(0);
  for (auto el : str) {
    data[line].push_back(glyph_t(el));
  }
}

std::string Sequence::GetStringAt(size_t line) {

  assert(data.size() > line);

  std::string ans;
  ans.resize(data[line].size());

  size_t num = 0;
  for (auto glyph : data[line]) {
    ans[num++] = glyph;
  }
  return ans;
}

void Sequence::AddLine(const std::string &str) {
  auto &line_vec = data.emplace_back();
  for (auto ch : str) {
    line_vec.push_back(ch);
  }
}

void Sequence::AddGlyphAt(size_t col, size_t line, glyph_t glyph) {
  auto &buffer = GetLineAt(line);

  buffer.insert(buffer.begin() + col, glyph);
}

VimktorErr_t Sequence::LoadFile(std::fstream &file) {

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
  return VIMKTOR_OK;
}
