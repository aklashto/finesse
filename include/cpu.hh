#ifndef CPU_HH
#define CPU_HH

#include "memory.hh"

/**
 * The NES CPU
 */
class Cpu {
 private:
  Memory* memory_;
  uint32_t pc_;

 public:
  // TODO: Add instructions and map to opcodes
};

#endif
