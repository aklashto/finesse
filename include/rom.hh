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
 * mappers
 */
class Rom {
 public:
  enum MirroringDirection { Horizontal = 0, Vertical = 1, None };

 private:
  Header header_;
  // Used for nametable mirroring, used by the PPU to lay out backgrounds
  MirroringDirection mirror_dir_;
  // Mapper code used for memory mapping cartridge hardware
  uint8_t mapper_;
  // Trainer Data
  std::vector<uint8_t> trainer_data_;
  // PRG (program) ROM
  std::vector<uint8_t> prg_rom_data_;
  // CHR (character) ROM
  std::vector<uint8_t> chr_rom_data_;
  // All ROMs start with "NES^Z"
  static constexpr std::array<uint8_t, 4> header_prefix_chars_{0x4E, 0x45, 0x53,
                                                               0x1A};
  // Size of header in bytes
  static constexpr size_t header_size_ = 16;
  // Number of used flags in the header
  static constexpr size_t num_flags_in_header_ = 2;

 public:
  Rom(Header& header, std::vector<uint8_t>& trainer_data,
      std::vector<uint8_t>& prg_rom_data, std::vector<uint8_t>& chr_rom_data);
  ~Rom();

  // Check that the given input header prefix matches the spec
  static bool CheckHeaderPrefix(char c, size_t pos);
  static size_t HeaderSize();
  static size_t HeaderPrefixSize();
  // Returns the current number of flags implemented in the header
  static size_t NumFlagsInHeader();
  // Returns the number of remaining header bytes which should be skipped
  static size_t UnusedHeaderBytes();
  Header& GetHeader();
  void PrintHeader();
};

#endif
