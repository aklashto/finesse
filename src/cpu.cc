#include "cpu.hh"

Cpu::Cpu(CpuMemory* memory)
    : memory_(memory),
      pc_(0xFFFC),
      reg_accumulator_(0),
      reg_index_x_(0),
      reg_index_y_(0) {
  reg_status_.reset();
}

Cpu::~Cpu() { delete memory_; }
