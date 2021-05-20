#ifndef ROM_HH
#define ROM_HH

#include <array>
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
 * mappers. All member fields in this class should be constants to reflect the
 * read-only nature of a ROM.
 */
class Rom {
 public:
  enum MirroringDirection { Horizontal = 0, Vertical = 1, None };
  enum Version { Archaic = 0, iNes = 1, iNes2_0 = 2 };

 private:
  const Header header_;
  // Used for nametable mirroring, used by the PPU to lay out backgrounds
  const MirroringDirection mirror_dir_;
  // Used to decode header and ROM contents
  const Version version_;
  // Mapper code used for memory mapping cartridge hardware
  const uint8_t mapper_;
  // Trainer Data
  const std::vector<uint8_t> trainer_data_;
  // PRG (program) ROM
  const std::vector<uint8_t> prg_rom_data_;
  // CHR (character) ROM
  const std::vector<uint8_t> chr_rom_data_;
  // All ROMs start with "NES^Z"
  static constexpr std::array<uint8_t, 4> header_prefix_chars_{0x4E, 0x45, 0x53,
                                                               0x1A};
  // Size of header in bytes
  static constexpr size_t header_size_ = 16;

 public:
  Rom(Header& header, MirroringDirection mirror_dir, Version version,
      uint8_t mapper, std::vector<uint8_t>& trainer_data,
      std::vector<uint8_t>& prg_rom_data, std::vector<uint8_t>& chr_rom_data);
  ~Rom();

  // Check that the given input header prefix matches the spec
  static bool CheckHeaderPrefix(char c, size_t pos);
  static size_t HeaderSize();
  static size_t HeaderPrefixSize();
  static size_t NumFlagsInHeader();
  void PrintHeader();
};

#endif
