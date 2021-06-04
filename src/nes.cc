#include "nes.hh"

#include <spdlog/spdlog.h>

#include <iostream>

Nes::Nes(Rom* rom) {
  CpuMemory* mem = new CpuMemory(rom->GetPrgRom());
  cpu_ = new Cpu(mem);
}

Nes::~Nes() { delete cpu_; }

void Nes::Run() { cpu_->Run(); }
