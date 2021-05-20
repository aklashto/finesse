#include "nes.hh"

#include <spdlog/spdlog.h>

#include <iostream>

#include "rom.hh"

Nes::Nes() {}
Nes::~Nes() {}
bool Nes::ReadInputFile(std::ifstream& infile) {
  // Check and store the ROM header prefix
  char c;
  Header header;
  for (size_t i = 0; i < Rom::HeaderPrefixSize(); ++i) {
    c = infile.get();
    if (infile.eof()) {
      spdlog::error("Unexpected EOF detected in ROM");
      return false;
    }
    if (!Rom::CheckHeaderPrefix(c, i)) {
      spdlog::error("Invalid prefix detected in ROM header");
      return false;
    }
    header.prefix.emplace_back(c);
  }

  // Get size of PRG and CHR ROM banks
  header.prg_size = infile.get();
  header.chr_size = infile.get();

  // Get remaining flags from the file
  for (size_t i = 0; i < Rom::NumFlagsInHeader(); ++i) {
    c = infile.get();
    if (infile.eof()) {
      spdlog::error("Unexpected EOF detected in ROM");
      return false;
    }
    header.flags.emplace_back(c);
  }

  // Advance cursor to end of header
  infile.seekg(Rom::UnusedHeaderBytes(), std::ios_base::cur);

  // Get trainer data
  std::vector<uint8_t> trainer_data;
  if (header.flags[0] >> 2 & 1) {
    for (size_t i = 0; i < 512; ++i) {
      c = infile.get();
      trainer_data.emplace_back(c);
    }
  }

  // Get prg rom data
  std::vector<uint8_t> prg_rom_data;
  for (size_t i = 0; i < 16384 * header.prg_size; ++i) {
    c = infile.get();
    prg_rom_data.emplace_back(c);
  }

  // Get chr rom data
  std::vector<uint8_t> chr_rom_data;
  for (size_t i = 0; i < 8192 * header.chr_size; ++i) {
    c = infile.get();
    chr_rom_data.emplace_back(c);
  }

  Rom* rom = new Rom(header, trainer_data, prg_rom_data, chr_rom_data);

  rom->PrintHeader();

  delete rom;

  return true;
}
