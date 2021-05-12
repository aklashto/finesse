#include "nes.hh"

#include <spdlog/spdlog.h>

#include <iostream>

Nes::Nes() {}
Nes::~Nes() {}
void Nes::ReadInputFile(std::ifstream& infile) {
  if (infile.peek() == std::ifstream::traits_type::eof()) return;
  spdlog::info("Non-empty .nes file provided!");

  char c;
  for (;;) {
    c = infile.get();
    if (infile.eof()) break;
    if (c == 'N') break;
  }
}
