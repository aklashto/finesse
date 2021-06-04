#include "rom.hh"

#include <spdlog/spdlog.h>

#include <cassert>
#include <string>

Rom::Rom(Header& header, MirroringDirection mirror_dir, Version version,
         uint8_t mapper, std::vector<uint8_t>& trainer_data,
         std::vector<uint8_t>& prg_rom_data, std::vector<uint8_t>& chr_rom_data)
    : header_(header),
      mirror_dir_(mirror_dir),
      version_(version),
      mapper_(mapper),
      trainer_data_(trainer_data),
      prg_rom_data_(prg_rom_data),
      chr_rom_data_(chr_rom_data) {}

Rom::~Rom() {}

bool Rom::CheckHeaderPrefix(char c, size_t pos) {
  assert(pos < 4);
  return c == header_prefix_chars_[pos];
}

size_t Rom::HeaderSize() { return header_size_; }

size_t Rom::HeaderPrefixSize() { return header_prefix_chars_.size(); }

size_t Rom::NumFlagsInHeader() {
  return header_size_ - header_prefix_chars_.size() - 2;
}

void Rom::PrintHeader() {
  spdlog::info("== Header Data ==");
  std::string s;
  for (const auto& c : header_.prefix) {
    s += c;
  }

  spdlog::info("Prefix: {0}", s);
  spdlog::info("PRG: {0} Kbytes", header_.prg_size * 16);
  spdlog::info("CHR: {0} Kbytes", header_.chr_size * 8);

  for (size_t i = 0; i < header_.flags.size(); ++i) {
    spdlog::info("Flag {0}: {1:8b}", i, header_.flags[i]);
  }

  spdlog::info("Mapper: {0:x}", mapper_);

  spdlog::info("=================");
}

const std::vector<uint8_t>& Rom::GetPrgRom() { return prg_rom_data_; }

const std::vector<uint8_t>& Rom::GetChrRom() { return chr_rom_data_; }

const std::vector<uint8_t>& Rom::GetTrainer() { return trainer_data_; }
