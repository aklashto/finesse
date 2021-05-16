#ifndef ROM_HH
#define ROM_HH

#include <cstdint>
#include <vector>

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
  // All ROMs start with "NES" followed by a SUB char
  const std::vector<uint8_t> header_prefix_chars_{0x4E, 0x45, 0x53, 0x1A};

 public:
  Rom();
  ~Rom();

  struct Header {
    std::vector<uint8_t> prefix;
    // in 16 KB units
    uint8_t prg_size;
    // in 8 KB units
    uint8_t chr_size;
    std::vector<uint8_t> flags;
  };

  Header header_;

  bool CheckHeaderPrefix(char c, size_t pos);
};

#endif
