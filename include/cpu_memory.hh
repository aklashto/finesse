#ifndef CPU_MEMORY_HH
#define CPU_MEMORY_HH

#include <array>
#include <cstdint>
#include <vector>

#include "memory.hh"

class CpuMemory : public Memory {
 private:
  std::array<uint8_t, 2048> ram_data_;
  std::array<uint8_t, 8> ppu_registers_;
  std::array<uint8_t, 24> apu_io_registers_;
  const std::vector<uint8_t> prg_rom_data_;

 public:
  CpuMemory(const std::vector<uint8_t>& prg_rom_data);
  ~CpuMemory() {}
  uint8_t Read(const uint32_t address);
  void Write(const uint32_t address, const uint8_t data);
};

#endif
