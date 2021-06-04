#include "cpu_memory.hh"

#include <spdlog/spdlog.h>

CpuMemory::CpuMemory(const std::vector<uint8_t>& prg_rom_data)
    : prg_rom_data_(prg_rom_data) {
  ram_data_.fill(0);
  ppu_registers_.fill(0);
  apu_io_registers_.fill(0);
}

uint8_t CpuMemory::Read(const uint16_t address) {
  if (address < 0x2000) {  // 2 KB internal RAM + 3 mirrors
    return ram_data_[address % 0x0800];
  } else if (address < 0x4000) {  // PPU register space
    return ppu_registers_[address % 8];
  } else if (address < 0x4018) {  // APU and I/O register space
    return apu_io_registers_[address - 0x4000];
  } else if (address > 0x8000) {  // PRG ROM space
    return prg_rom_data_.at(address - 0x8000);
  } else {
    spdlog::error("Tried to read unimplemented address {0:4x} in CPU memory",
                  address);
    assert(false);
  }
}

uint16_t CpuMemory::ReadDoubleByte(const uint16_t address) {
  return Read(address) | ((uint16_t) Read(address + 1) << 8);
}

void CpuMemory::Write(const uint16_t address, const uint8_t data) {
  if (address < 0x2000) {  // 2 KB internal RAM + 3 mirrors
    ram_data_[address % 0x0800] = data;
  } else if (address < 0x4000) {  // PPU register space
    ppu_registers_[address % 8] = data;
  } else if (address < 0x4018) {  // APU and I/O register space
    apu_io_registers_[address - 0x4000] = data;
  } else {
    spdlog::error(
        "Tried to write unimplemented or illegal address {0:4x} in CPU memory",
        address);
    assert(false);
  }
}
