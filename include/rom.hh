#ifndef ROM_HH
#define ROM_HH

#include <cstdint>

/**
 * Container class for the input ROM, which holds program and data for NES
 * games as well as metadata information about each game and their respective
 * mappers
 */
class Rom {
 private:
  // PRG (program) ROM size, in units of 16 KB
  uint8_t prg_size_;
  // CHR (character) ROM size, in units of 8 KB
  uint8_t chr_size_;

 public:
  Rom(uint8_t prg_size, uint8_t chr_size);
  ~Rom();
};

#endif
