// #include <gtkmm.h>
#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>

#include "nes.hh"
#include "rom.hh"

inline bool ends_with(const std::string& input, const std::string& suffix) {
  size_t suffix_length = suffix.length();
  size_t input_length = input.length();
  if (suffix_length > input_length) {
    return false;
  }
  return !(input.compare(input_length - suffix_length, suffix_length, suffix));
}

Rom* ReadInputFile(std::ifstream& infile) {
  // Check and store the ROM header prefix
  char c;
  Header header;
  for (size_t i = 0; i < Rom::HeaderPrefixSize(); ++i) {
    c = infile.get();
    if (infile.eof()) {
      spdlog::error("Unexpected EOF detected in ROM");
      return nullptr;
    }
    if (!Rom::CheckHeaderPrefix(c, i)) {
      spdlog::error("Invalid prefix detected in ROM header");
      return nullptr;
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
      return nullptr;
    }
    header.flags.emplace_back(c);
  }

  // Extract version and associated mapper
  Rom::Version version;
  uint8_t mapper;
  if ((header.flags[1] & 0xC) == 8) {
    spdlog::error("NES 2.0 ROM format not yet supported");
    return nullptr;
  } else if (!(header.flags[1] & 0xC) &&
             std::all_of(header.flags.cbegin() + 6, header.flags.cend(),
                         [](uint8_t flag) { return flag == 0; })) {
    version = Rom::Version::iNes;
    mapper = (header.flags[0] >> 4) | ((header.flags[1] << 4) >> 4);
    header.flags.resize(4);
  } else {
    version = Rom::Version::Archaic;
    mapper = header.flags[0] >> 4;
    header.flags.resize(1);
  }

  // Extract mirroring direction
  Rom::MirroringDirection mirror_dir;
  if (header.flags[0] >> 3 & 1) {
    mirror_dir = header.flags[0] & 1 ? Rom::MirroringDirection::Vertical
                                     : Rom::MirroringDirection::Horizontal;
  } else {
    mirror_dir = Rom::MirroringDirection::None;
  }

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

  Rom* rom = new Rom(header, mirror_dir, version, mapper, trainer_data,
                     prg_rom_data, chr_rom_data);

  return rom;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    spdlog::error("{} takes an input file as argument.", argv[0]);
    spdlog::error("  Usage: {} <filename>.nes", argv[0]);
    return -1;
  }

  std::string input_name(argv[1]);
  if (!ends_with(input_name, ".nes")) {
    spdlog::error("Argument must be a file name with a .nes extension");
    return -2;
  }

  std::ifstream infile(input_name, std::ios::in | std::ios::binary);

  if (!infile.is_open()) {
    spdlog::error("Failed to open test file {}", input_name);
    return -3;
  }

  Rom* rom = ReadInputFile(infile);
  if (!rom) {
    return -4;
  }

  rom->PrintHeader();

  /*
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    Gtk::Window window;
    window.set_default_size(200, 200);

    return app->run(window);
    */

  Nes* nes = new Nes(rom);
  nes->Run();

  delete nes;
  delete rom;

  return 0;
}
