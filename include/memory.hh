#ifndef MEMORY_HH
#define MEMORY_HH

#include <cstdint>

/**
 * Base class to represents the general memory operations for the CPU and PPU
 */
class Memory {
 public:
  virtual ~Memory() {}
  virtual uint8_t Read(const uint16_t address) = 0;
  virtual uint16_t ReadDoubleByte(const uint16_t address) = 0;
  virtual void Write(const uint16_t address, const uint8_t data) = 0;
};

#endif
