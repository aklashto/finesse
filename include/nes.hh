#ifndef NES_HH
#define NES_HH

#include <fstream>

/**
 * The top-level of the emulated NES console. To start, this will just be the
 * CPU. Eventually, all components will be added here (e.g. PPU, APU, mappers)
 */
class Nes {
 public:
  Nes();
  ~Nes();
  void ReadInputFile(std::ifstream& infile);
};

#endif
