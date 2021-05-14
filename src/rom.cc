#include "rom.hh"

#include <cassert>

Rom::Rom() {}

bool Rom::CheckHeaderPrefix(char c, size_t pos) {
  assert(pos < 4);
  return c == header_prefix_chars_[pos];
}
