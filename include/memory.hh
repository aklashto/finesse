#ifndef MEMORY_HH
#define MEMORY_HH

/**
 * Base class to represents the general memory operations for the CPU and PPU
 */
class Memory {
 public:
  Memory();
  virtual ~Memory();
  virtual uint8_t Read() = 0;
  virtual void Write() = 0;
};

#endif
