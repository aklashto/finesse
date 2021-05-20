#include "rom.hh"

#include <spdlog/spdlog.h>

#include <cassert>
#include <string>

Rom::Rom(Header& header, std::vector<uint8_t>& trainer_data,
         std::vector<uint8_t>& prg_rom_data, std::vector<uint8_t>& chr_rom_data)
    : header_(header),
      trainer_data_(trainer_data),
      prg_rom_data_(prg_rom_data),
      chr_rom_data_(chr_rom_data) {
  if (header.flags[0] >> 3 & 1) {
    mirror_dir_ = header.flags[0] & 1 ? MirroringDirection::Vertical
                                      : MirroringDirection::Horizontal;
  } else {
    mirror_dir_ = MirroringDirection::None;
  }

  mapper_ = (header.flags[0] >> 4) | ((header.flags[1] >> 4) << 4);
}

Rom::~Rom() {}

bool Rom::CheckHeaderPrefix(char c, size_t pos) {
  assert(pos < 4);
  return c == header_prefix_chars_[pos];
}

size_t Rom::HeaderSize() { return header_size_; }

size_t Rom::HeaderPrefixSize() { return header_prefix_chars_.size(); }

size_t Rom::NumFlagsInHeader() { return num_flags_in_header_; }

size_t Rom::UnusedHeaderBytes() {
  return header_size_ - header_prefix_chars_.size() - num_flags_in_header_;
}

Header& Rom::GetHeader() { return header_; }

void Rom::PrintHeader() {
  spdlog::info("== Header Data ==");
  std::string s;
  for (const auto& c : header_.prefix) {
    s += c;
  }

  spdlog::info("Prefix: {0}", s);
  spdlog::info("PRG: {0} bytes", header_.prg_size);
  spdlog::info("CHR: {0} bytes", header_.chr_size);

  for (size_t i = 0; i < num_flags_in_header_; ++i) {
    spdlog::info("Flag {0}: {1:x}", i, header_.flags[i]);
  }

  spdlog::info("Mapper: {0:x}", mapper_);

  spdlog::info("=================");
}
