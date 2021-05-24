#ifndef CPU_HH
#define CPU_HH

#include <bitset>
#include <cstdint>

#include "cpu_memory.hh"

/**
 * The NES CPU
 */
class Cpu {
 private:
  CpuMemory* memory_;
  uint16_t pc_;                // PC
  uint8_t sp_;                 // S
  uint8_t reg_accumulator_;    // A
  uint8_t reg_index_x_;        // X
  uint8_t reg_index_y_;        // Y
  std::bitset<8> reg_status_;  // P

  // Used to index into status register P
  enum StatusFlags {
    Carry = 0,
    Zero = 1,
    InterruptDisable = 2,
    Decimal = 3,
    Overflow = 6,
    Negative = 7
  };

 public:
  // TODO: Add instructions and map to opcodes
  Cpu(CpuMemory* memory);
  ~Cpu();
};

#endif
