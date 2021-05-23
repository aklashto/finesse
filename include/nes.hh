#ifndef NES_HH
#define NES_HH

#include <fstream>

#include "cpu.hh"

/**
 * The top-level of the emulated NES console. To start, this will just be the
 * CPU. Eventually, all components will be added here (e.g. PPU, APU, mappers)
 */
class Nes {
 private:
  Cpu* cpu_;

 public:
  Nes();
  ~Nes();
  // Returns whether read was successful
  bool ReadInputFile(std::ifstream& infile);
};

#endif
