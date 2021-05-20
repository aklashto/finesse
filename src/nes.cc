#include "nes.hh"

#include <spdlog/spdlog.h>

#include <iostream>

#include "rom.hh"

Nes::Nes() {}
Nes::~Nes() {}
bool Nes::ReadInputFile(std::ifstream& infile) {
  Rom* rom = new Rom();

  // Check and store the ROM header prefix
  char c;
  for (size_t i = 0; i < rom->HeaderPrefixSize(); ++i) {
    c = infile.get();
    if (infile.eof()) {
      spdlog::error("Unexpected EOF detected in ROM");
      return false;
    }
    if (!rom->CheckHeaderPrefix(c, i)) {
      spdlog::error("Invalid prefix detected in ROM header");
      return false;
    }
    rom->GetHeader().prefix.emplace_back(c);
  }

  // Get size of PRG and CHR ROM banks
  rom->GetHeader().prg_size = infile.get();
  rom->GetHeader().chr_size = infile.get();

  // Get remaining flags from the file
  for (size_t i = 0; i < rom->NumFlagsInHeader(); ++i) {
    c = infile.get();
    if (infile.eof()) {
      spdlog::error("Unexpected EOF detected in ROM");
      return false;
    }
    rom->GetHeader().flags.emplace_back(c);
  }

  /**
   * Flag 6
   *   0: Mirroring
   *   1: Cartridge contains battery-backed PRG RAM ($6000-7FFF) or other
   *      persistent memory
   *   2: 512-byte trainer at $7000-$71FF (stored before PRG data)
   *   3: Ignore mirroring control or above mirroring bit; instead provide
   *      four-screen VRAM 4-7: Mapper LSBs
   *
   * Flag 7
   *   0: VS Unisystem
   *   1: PlayChoice-10 (8KB of Hint Screen data stored after CHR data)
   *   2-3: If equal to 2, flags 8-15 are in NES 2.0 format
   *   4-7: Mapper MSBs
   */

  // Advance cursor to end of header
  infile.seekg(rom->UnusedHeaderBytes(), std::ios_base::cur);

  rom->PrintHeader();

  delete rom;

  return true;
}
