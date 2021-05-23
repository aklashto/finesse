#ifndef CPU_HH
#define CPU_HH

#include "cpu_memory.hh"

/**
 * The NES CPU
 */
class Cpu {
 private:
  CpuMemory* memory_;
  uint32_t pc_;

 public:
  // TODO: Add instructions and map to opcodes
};

#endif
