#include "rom.hh"

#include <cassert>

Rom::Rom() {}

bool Rom::CheckHeaderPrefix(char c, size_t pos) {
  assert(pos < 4);

  switch (pos) {
    case 0:
      return c == 'N';
    case 1:
      return c == 'E';
    case 2:
      return c == 'S';
    case 3:
      return c == 0x1A;
  }

  return false;
}
