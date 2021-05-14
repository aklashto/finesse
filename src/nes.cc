#include "nes.hh"

#include <spdlog/spdlog.h>

#include <iostream>

#include "rom.hh"

Nes::Nes() {}
Nes::~Nes() {}
void Nes::ReadInputFile(std::ifstream& infile) {
  if (infile.peek() == std::ifstream::traits_type::eof()) return;
  spdlog::info("Non-empty .nes file provided!");

  Rom* rom = new Rom();

  rom->header_.prg_size = 0;
  rom->header_.chr_size = 0;

  char c;
  for (size_t i = 0; i < 4; ++i) {
    c = infile.get();
    if (infile.eof()) return;                   // TODO: generate error
    if (!rom->CheckHeaderPrefix(c, i)) return;  // TODO: generate error
    rom->header_.prefix.emplace_back(c);
  }

  for (;;) {
    c = infile.get();
    if (infile.eof()) break;
    if (c == 'N') break;
  }
}
