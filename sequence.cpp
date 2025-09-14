#include "sequence.h"
#include <assert.h>
#include <fstream>
Sequence::Sequence(std::fstream &file) {

  data.reserve(DEFAULT_SEQUENCE_LINE_NUM);

  std::string line;

  while (file >> line) {
    auto element = data.emplace_back(std::vector<glyph_t>());
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
