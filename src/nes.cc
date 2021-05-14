#include "nes.hh"

#include <spdlog/spdlog.h>

#include <iostream>

#include "rom.hh"

Nes::Nes() {}
Nes::~Nes() {}
bool Nes::ReadInputFile(std::ifstream& infile) {
  Rom* rom = new Rom();

  rom->header_.prg_size = 0;
  rom->header_.chr_size = 0;

  // Check and store the ROM header prefix
  char c;
  for (size_t i = 0; i < 4; ++i) {
    c = infile.get();
    if (infile.eof()) {
      spdlog::error("Unexpected EOF detected in ROM");
      return false;
    }
    if (!rom->CheckHeaderPrefix(c, i)) {
      spdlog::error("Invalid prefix detected in ROM header");
      return false;
    }
    rom->header_.prefix.emplace_back(c);
  }

  for (;;) {
    c = infile.get();
    if (infile.eof()) break;
    if (c == 'N') break;
  }

  return true;
}
