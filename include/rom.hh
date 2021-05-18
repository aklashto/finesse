#ifndef ROM_HH
#define ROM_HH

#include <cstdint>
#include <vector>

/**
 * Container for INES header
 */
struct Header {
  std::vector<uint8_t> prefix;
  // in 16 KB units
  uint8_t prg_size;
  // in 8 KB units
  uint8_t chr_size;
  std::vector<uint8_t> flags;
};

/**
 * Container class for the input ROM, which holds program and data for NES
 * games as well as metadata information about each game and their respective
 * mappers
 */
class Rom {
 private:
  // PRG (program) ROM
  std::vector<uint8_t> prg_rom_data_;
  // CHR (character) ROM
  std::vector<uint8_t> chr_rom_data_;
  // All ROMs start with "NES^Z"
  const std::vector<uint8_t> header_prefix_chars_{0x4E, 0x45, 0x53, 0x1A};
  // Size of header in bytes
  const size_t header_size_ = 16;
  // Number of used flags in the header
  const size_t num_flags_in_header_ = 2;

  Header header_;

 public:
  Rom();
  ~Rom();

  // Check that the given input header prefix matches the spec
  bool CheckHeaderPrefix(char c, size_t pos);
  size_t HeaderSize();
  size_t HeaderPrefixSize();
  // Returns the current number of flags implemented in the header
  size_t NumFlagsInHeader();
  // Returns the number of remaining header bytes which should be skipped
  size_t UnusedHeaderBytes();
  Header& GetHeader();
  void PrintHeader();
};

#endif
