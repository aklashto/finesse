#include "rom.hh"

#include <spdlog/spdlog.h>

#include <cassert>
#include <string>

Rom::Rom() {}

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

  spdlog::info("=================");
}
