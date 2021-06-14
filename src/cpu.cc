#include "cpu.hh"

Cpu::Cpu(CpuMemory* memory) : memory_(memory), S(0xFF), A(0), X(0), Y(0) {
  PC = memory->ReadDoubleByte(0xFFFC);
  P.reset();
}

Cpu::~Cpu() { delete memory_; }

uint8_t Cpu::Pull() {
  uint16_t addr = 0x100 | (uint16_t)(S++);
  return memory_->Read(addr);
}

void Cpu::Push(const uint8_t val) {
  uint16_t addr = 0x100 | (uint16_t)(S--);
  memory_->Write(addr, val);
}

void Cpu::SetStatusFlag(const StatusFlag flag, const bool condition) {
  if (condition) {
    P[flag] = 1;
  } else {
    P[flag] = 0;
  }
}

void Cpu::SetFlagZ(const uint8_t val) { SetStatusFlag(Zero, val == 0); }

void Cpu::SetFlagN(const uint8_t val) {
  SetStatusFlag(Negative, val >> 7 == 1);
}

void Cpu::Exec(const uint8_t opcode) {
  switch (opcode) {
    case 0x00: return BRK();
    case 0x01: return ORA(IndexedIndirectX);
    case 0x02: return STP();
    case 0x03: return SLO(IndexedIndirectX);
    case 0x04: return NOP(ZeroPage);
    case 0x05: return ORA(ZeroPage);
    case 0x06: return ASL(ZeroPage);
    case 0x07: return SLO(ZeroPage);
    case 0x08: return PHP();
    case 0x09: return ORA(Immediate);
    case 0x0A: return ASL();
    case 0x0B: return ANC(Immediate);
    case 0x0C: return NOP(Absolute);
    case 0x0D: return ORA(Absolute);
    case 0x0E: return ASL(Absolute);
    case 0x0F: return SLO(Absolute);
    case 0x10: return BPL(Relative);
    case 0x11: return ORA(IndexedIndirectY);
    case 0x12: return STP();
    case 0x13: return SLO(IndexedIndirectY);
    case 0x14: return NOP(IndexedZeroPageX);
    case 0x15: return ORA(IndexedZeroPageX);
    case 0x16: return ASL(IndexedZeroPageX);
    case 0x17: return SLO(IndexedZeroPageX);
    case 0x18: return CLC();
    case 0x19: return ORA(IndexedAbsoluteY);
    case 0x1A: return NOP();
    case 0x1B: return SLO(IndexedAbsoluteY);
    case 0x1C: return NOP(IndexedAbsoluteX);
    case 0x1D: return ORA(IndexedAbsoluteX);
    case 0x1E: return ASL(IndexedAbsoluteX);
    case 0x1F: return SLO(IndexedAbsoluteX);
    case 0x20: return JSR(Absolute);
    case 0x21: return AND(IndexedIndirectX);
    case 0x22: return STP();
    case 0x23: return RLA(IndexedIndirectX);
    case 0x24: return BIT(ZeroPage);
    case 0x25: return AND(ZeroPage);
    case 0x26: return ROL(ZeroPage);
    case 0x27: return RLA(ZeroPage);
    case 0x28: return PLP();
    case 0x29: return AND(Immediate);
    case 0x2A: return ROL();
    case 0x2B: return ANC(Immediate);
    case 0x2C: return BIT(Absolute);
    case 0x2D: return AND(Absolute);
    case 0x2E: return ROL(Absolute);
    case 0x2F: return RLA(Absolute);
    case 0x30: return BMI(Relative);
    case 0x31: return AND(IndexedIndirectY);
    case 0x32: return STP();
    case 0x33: return RLA(IndexedIndirectY);
    case 0x34: return NOP(IndexedZeroPageX);
    case 0x35: return AND(IndexedZeroPageX);
    case 0x36: return ROL(IndexedZeroPageX);
    case 0x37: return RLA(IndexedZeroPageX);
    case 0x38: return SEC();
    case 0x39: return AND(IndexedAbsoluteY);
    case 0x3A: return NOP();
    case 0x3B: return RLA(IndexedAbsoluteY);
    case 0x3C: return NOP(IndexedAbsoluteX);
    case 0x3D: return AND(IndexedAbsoluteX);
    case 0x3E: return ROL(IndexedAbsoluteX);
    case 0x3F: return RLA(IndexedAbsoluteX);
    case 0x40: return RTI();
    case 0x41: return EOR(IndexedIndirectX);
    case 0x42: return STP();
    case 0x43: return SRE(IndexedIndirectX);
    case 0x44: return NOP(ZeroPage);
    case 0x45: return EOR(ZeroPage);
    case 0x46: return LSR(ZeroPage);
    case 0x47: return SRE(ZeroPage);
    case 0x48: return PHA();
    case 0x49: return EOR(Immediate);
    case 0x4A: return LSR();
    case 0x4B: return ALR(Immediate);
    case 0x4C: return JMP(Absolute);
    case 0x4D: return EOR(Absolute);
    case 0x4E: return LSR(Absolute);
    case 0x4F: return SRE(Absolute);
    case 0x50: return BVC(Relative);
    case 0x51: return EOR(IndexedIndirectY);
    case 0x52: return STP();
    case 0x53: return SRE(IndexedIndirectY);
    case 0x54: return NOP(IndexedZeroPageX);
    case 0x55: return EOR(IndexedZeroPageX);
    case 0x56: return LSR(IndexedZeroPageX);
    case 0x57: return SRE(IndexedZeroPageX);
    case 0x58: return CLI();
    case 0x59: return EOR(IndexedAbsoluteY);
    case 0x5A: return NOP();
    case 0x5B: return SRE(IndexedAbsoluteY);
    case 0x5C: return NOP(IndexedAbsoluteX);
    case 0x5D: return EOR(IndexedAbsoluteX);
    case 0x5E: return LSR(IndexedAbsoluteX);
    case 0x5F: return SRE(IndexedAbsoluteX);
    case 0x60: return RTS();
    case 0x61: return ADC(IndexedIndirectX);
    case 0x62: return STP();
    case 0x63: return RRA(IndexedIndirectX);
    case 0x64: return NOP(ZeroPage);
    case 0x65: return ADC(ZeroPage);
    case 0x66: return ROR(ZeroPage);
    case 0x67: return RRA(ZeroPage);
    case 0x68: return PLA();
    case 0x69: return ADC(Immediate);
    case 0x6A: return ROR();
    case 0x6B: return ARR(Immediate);
    case 0x6C: return JMP(Indirect);
    case 0x6D: return ADC(Absolute);
    case 0x6E: return ROR(Absolute);
    case 0x6F: return RRA(Absolute);
    case 0x70: return BVS(Relative);
    case 0x71: return ADC(IndexedIndirectY);
    case 0x72: return STP();
    case 0x73: return RRA(IndexedIndirectY);
    case 0x74: return NOP(IndexedZeroPageX);
    case 0x75: return ADC(IndexedZeroPageX);
    case 0x76: return ROR(IndexedZeroPageX);
    case 0x77: return RRA(IndexedZeroPageX);
    case 0x78: return SEI();
    case 0x79: return ADC(IndexedAbsoluteY);
    case 0x7A: return NOP();
    case 0x7B: return RRA(IndexedAbsoluteY);
    case 0x7C: return NOP(IndexedAbsoluteX);
    case 0x7D: return ADC(IndexedAbsoluteX);
    case 0x7E: return ROR(IndexedAbsoluteX);
    case 0x7F: return RRA(IndexedAbsoluteX);
    case 0x80: return NOP(Immediate);
    case 0x81: return STA(IndexedIndirectX);
    case 0x82: return NOP(Immediate);
    case 0x83: return SAX(IndexedIndirectX);
    case 0x84: return STY(ZeroPage);
    case 0x85: return STA(ZeroPage);
    case 0x86: return STX(ZeroPage);
    case 0x87: return SAX(ZeroPage);
    case 0x88: return DEY();
    case 0x89: return NOP(Immediate);
    case 0x8A: return TXA();
    case 0x8B: return XAA(Immediate);
    case 0x8C: return STY(Absolute);
    case 0x8D: return STA(Absolute);
    case 0x8E: return STX(Absolute);
    case 0x8F: return SAX(Absolute);
    case 0x90: return BCC(Relative);
    case 0x91: return STA(IndexedIndirectY);
    case 0x92: return STP();
    case 0x93: return AHX(IndexedIndirectY);
    case 0x94: return STY(IndexedZeroPageX);
    case 0x95: return STA(IndexedZeroPageX);
    case 0x96: return STX(IndexedZeroPageY);
    case 0x97: return SAX(IndexedZeroPageY);
    case 0x98: return TYA();
    case 0x99: return STA(IndexedAbsoluteY);
    case 0x9A: return TXS();
    case 0x9B: return TAS(IndexedAbsoluteY);
    case 0x9C: return SHY(IndexedAbsoluteX);
    case 0x9D: return STA(IndexedAbsoluteX);
    case 0x9E: return SHX(IndexedAbsoluteX);
    case 0x9F: return AHX(IndexedAbsoluteX);
    case 0xA0: return LDY(Immediate);
    case 0xA1: return LDA(IndexedIndirectX);
    case 0xA2: return LDX(Immediate);
    case 0xA3: return LAX(IndexedIndirectX);
    case 0xA4: return LDY(ZeroPage);
    case 0xA5: return LDA(ZeroPage);
    case 0xA6: return LDX(ZeroPage);
    case 0xA7: return LAX(ZeroPage);
    case 0xA8: return TAY();
    case 0xA9: return LDA(Immediate);
    case 0xAA: return TAX();
    case 0xAB: return LAX(Immediate);
    case 0xAC: return LDY(Absolute);
    case 0xAD: return LDA(Absolute);
    case 0xAE: return LDX(Absolute);
    case 0xAF: return LAX(Absolute);
    case 0xB0: return BCS(Relative);
    case 0xB1: return LDA(IndexedIndirectY);
    case 0xB2: return STP();
    case 0xB3: return LAX(IndexedIndirectY);
    case 0xB4: return LDY(IndexedZeroPageX);
    case 0xB5: return LDA(IndexedZeroPageX);
    case 0xB6: return LDX(IndexedZeroPageY);
    case 0xB7: return LAX(IndexedZeroPageY);
    case 0xB8: return CLV();
    case 0xB9: return LDA(IndexedAbsoluteY);
    case 0xBA: return TSX();
    case 0xBB: return LAS(IndexedAbsoluteY);
    case 0xBC: return LDY(IndexedAbsoluteX);
    case 0xBD: return LDA(IndexedAbsoluteX);
    case 0xBE: return LDX(IndexedAbsoluteX);
    case 0xBF: return LAX(IndexedAbsoluteX);
    case 0xC0: return CPY(Immediate);
    case 0xC1: return CMP(IndexedIndirectX);
    case 0xC2: return NOP(Immediate);
    case 0xC3: return DCP(IndexedIndirectX);
    case 0xC4: return CPY(ZeroPage);
    case 0xC5: return CMP(ZeroPage);
    case 0xC6: return DEC(ZeroPage);
    case 0xC7: return DCP(ZeroPage);
    case 0xC8: return INY();
    case 0xC9: return CMP(Immediate);
    case 0xCA: return DEX();
    case 0xCB: return AXS(Immediate);
    case 0xCC: return CPY(Absolute);
    case 0xCD: return CMP(Absolute);
    case 0xCE: return DEC(Absolute);
    case 0xCF: return DCP(Absolute);
    case 0xD0: return BNE(Relative);
    case 0xD1: return CMP(IndexedIndirectY);
    case 0xD2: return STP();
    case 0xD3: return DCP(IndexedIndirectY);
    case 0xD4: return NOP(IndexedZeroPageX);
    case 0xD5: return CMP(IndexedZeroPageX);
    case 0xD6: return DEC(IndexedZeroPageX);
    case 0xD7: return DCP(IndexedZeroPageX);
    case 0xD8: return CLD();
    case 0xD9: return CMP(IndexedAbsoluteY);
    case 0xDA: return NOP();
    case 0xDB: return DCP(IndexedAbsoluteY);
    case 0xDC: return NOP(IndexedAbsoluteX);
    case 0xDD: return CMP(IndexedAbsoluteX);
    case 0xDE: return DEC(IndexedAbsoluteX);
    case 0xDF: return DCP(IndexedAbsoluteX);
    case 0xE0: return CPX(Immediate);
    case 0xE1: return SBC(IndexedIndirectX);
    case 0xE2: return NOP(Immediate);
    case 0xE3: return ISC(IndexedIndirectX);
    case 0xE4: return CPX(ZeroPage);
    case 0xE5: return SBC(ZeroPage);
    case 0xE6: return INC(ZeroPage);
    case 0xE7: return ISC(ZeroPage);
    case 0xE8: return INX();
    case 0xE9: return SBC(Immediate);
    case 0xEA: return NOP();
    case 0xEB: return SBC(Immediate);
    case 0xEC: return CPX(Absolute);
    case 0xED: return SBC(Absolute);
    case 0xEE: return INC(Absolute);
    case 0xEF: return ISC(Absolute);
    case 0xF0: return BEQ(Relative);
    case 0xF1: return SBC(IndexedIndirectY);
    case 0xF2: return STP();
    case 0xF3: return ISC(IndexedIndirectY);
    case 0xF4: return NOP(IndexedZeroPageX);
    case 0xF5: return SBC(IndexedZeroPageX);
    case 0xF6: return INC(IndexedZeroPageX);
    case 0xF7: return ISC(IndexedZeroPageX);
    case 0xF8: return SED();
    case 0xF9: return SBC(IndexedAbsoluteY);
    case 0xFA: return NOP();
    case 0xFB: return ISC(IndexedAbsoluteY);
    case 0xFC: return NOP(IndexedAbsoluteX);
    case 0xFD: return SBC(IndexedAbsoluteX);
    case 0xFE: return INC(IndexedAbsoluteX);
    case 0xFF: return ISC(IndexedAbsoluteX);
  }
}

uint16_t Cpu::ExecuteAddressingMode(const AddressingMode mode) {
  assert(mode != Implicit);

  switch (mode) {
    case IndexedZeroPageX: return (X + memory_->Read(++PC)) & 0xFF;
    case IndexedZeroPageY: return (Y + memory_->Read(++PC)) & 0xFF;
    case IndexedAbsoluteX: return X + memory_->ReadDoubleByte(++PC);
    case IndexedAbsoluteY: return Y + memory_->ReadDoubleByte(++PC);
    // case IndexedIndirectX:
    // case IndexedIndirectY:
    // case Accumulator:
    case Immediate: return ++PC;
    case ZeroPage: return memory_->Read(++PC);
    case Absolute: return memory_->ReadDoubleByte(++PC);
    case Relative: {
      int8_t offset = (int8_t)(memory_->Read(++PC));
      // return (++PC) + offset;
      return PC + offset;
    }
    case Indirect:
      return memory_->ReadDoubleByte(memory_->ReadDoubleByte(++PC));
    // case Implicit:
    default: return 0;
  }
}

void Cpu::Run() {
  for (;; ++PC) {
    Exec(memory_->Read(PC));
  }
}

void Cpu::ADC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX ||
         mode == IndexedAbsoluteY || mode == IndexedIndirectX ||
         mode == IndexedIndirectY);

  uint8_t M = memory_->Read(ExecuteAddressingMode(mode));
  uint16_t val = A + M + P[Carry];

  SetStatusFlag(Carry, val > 0xFF);

  // Overflow means the inputs are the same sign and the result is a different
  // sign, so we compare the MSB which is the sign bit in 2s complement
  SetStatusFlag(Overflow, ((A ^ M) >> 7) == 0 && (((A ^ val) >> 7) & 1) == 1);

  // Implicit cast from 16-bit to 8-bit to get truncated value
  A = val;

  SetFlagN(A);
  SetFlagZ(A);
}
void Cpu::AHX(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::ALR(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::ANC(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::AND(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX ||
         mode == IndexedAbsoluteY || mode == IndexedIndirectX ||
         mode == IndexedIndirectY);

  A &= memory_->Read(ExecuteAddressingMode(mode));
  SetFlagN(A);
  SetFlagZ(A);
}
void Cpu::ARR(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::ASL(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Accumulator || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX);

  uint8_t val;

  if (mode == Accumulator) {
    val = A;
    A = val * 2;
  } else {
    uint8_t addr = ExecuteAddressingMode(mode);
    val = memory_->Read(addr);
    memory_->Write(addr, val * 2);
  }

  SetStatusFlag(Carry, val >> 7 == 1);

  SetFlagN(val);
  SetFlagZ(val);
}
void Cpu::AXS(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::BCC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (!P[Carry]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::BCS(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (P[Carry]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::BEQ(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (P[Zero]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::BIT(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative || mode == ZeroPage);

  uint8_t M = memory_->Read(ExecuteAddressingMode(mode));

  SetFlagZ(A & M);
  P[Overflow] = (M >> 5) & 1;
  P[Negative] = (M >> 6) & 1;
}
void Cpu::BMI(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (P[Negative]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::BNE(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (!P[Zero]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::BPL(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (!P[Negative]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::BRK(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  Push(PC >> 8);
  Push(PC & 0xFF);
  Push(P.to_ulong());

  PC = memory_->ReadDoubleByte(0xFFFE);
  SetStatusFlag(Break, true);
}
void Cpu::BVC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (!P[Overflow]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::BVS(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Relative);

  if (P[Overflow]) {
    PC = ExecuteAddressingMode(mode);
  }
}
void Cpu::CLC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetStatusFlag(Carry, false);
}
void Cpu::CLD(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetStatusFlag(Decimal, false);
}
void Cpu::CLI(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetStatusFlag(InterruptDisable, false);
}
void Cpu::CLV(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetStatusFlag(Overflow, false);
}
void Cpu::CMP(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX ||
         mode == IndexedAbsoluteY || mode == IndexedIndirectX ||
         mode == IndexedIndirectY);

  uint8_t M = memory_->Read(ExecuteAddressingMode(mode));
  uint8_t val = A - M;
  SetFlagN(val);
  SetFlagZ(val);
  SetStatusFlag(Carry, A >= M);
}
void Cpu::CPX(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == Absolute);

  uint8_t M = memory_->Read(ExecuteAddressingMode(mode));

  SetStatusFlag(Carry, (int8_t)X >= (int8_t)M);

  uint8_t val = X - M;
  SetFlagN(val);
  SetFlagZ(val);
}
void Cpu::CPY(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == Absolute);

  uint8_t M = memory_->Read(ExecuteAddressingMode(mode));

  SetStatusFlag(Carry, (int8_t)Y >= (int8_t)M);

  uint8_t val = Y - M;
  SetFlagN(val);
  SetFlagZ(val);
}
void Cpu::DCP(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::DEC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == ZeroPage || mode == IndexedZeroPageX || mode == Absolute ||
         mode == IndexedAbsoluteX);

  uint16_t addr = ExecuteAddressingMode(mode);
  uint8_t M = memory_->Read(addr);
  memory_->Write(addr, --M);

  SetFlagN(M);
  SetFlagZ(M);
}
void Cpu::DEX(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetFlagN(--X);
  SetFlagZ(X);
}
void Cpu::DEY(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetFlagN(--Y);
  SetFlagZ(Y);
}
void Cpu::EOR(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX ||
         mode == IndexedAbsoluteY || mode == IndexedIndirectX ||
         mode == IndexedIndirectY);

  A ^= memory_->Read(ExecuteAddressingMode(mode));
  SetFlagN(A);
  SetFlagZ(A);
}
void Cpu::INC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == ZeroPage || mode == IndexedZeroPageX || mode == Absolute ||
         mode == IndexedAbsoluteX);

  uint16_t addr = ExecuteAddressingMode(mode);
  uint8_t M = memory_->Read(addr);
  memory_->Write(addr, ++M);

  SetFlagN(M);
  SetFlagZ(M);
}
void Cpu::INX(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetFlagN(++X);
  SetFlagZ(X);
}
void Cpu::INY(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetFlagN(++Y);
  SetFlagZ(Y);
}
void Cpu::ISC(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::JMP(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Absolute || mode == Indirect);

  uint16_t addr = ExecuteAddressingMode(mode);
  uint8_t upper, lower;

  // Emulating 6502 bug which reads from the wrong byte in memory
  if (mode == Indirect && addr & 0xFF) {
    lower = memory_->Read(addr);
    upper = memory_->Read(addr - 0xFF);
    PC = lower | (uint16_t)upper << 8;
  } else {
    PC = memory_->ReadDoubleByte(addr);
  }
}
void Cpu::JSR(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Absolute);

  uint16_t addr = memory_->ReadDoubleByte(ExecuteAddressingMode(mode));
  Push(PC >> 8);
  Push(PC & 0xFF);

  PC = addr;
}
void Cpu::LAS(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::LAX(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::LDA(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX ||
         mode == IndexedAbsoluteY || mode == IndexedIndirectX ||
         mode == IndexedIndirectY);

  A = memory_->Read(ExecuteAddressingMode(mode));
  SetFlagZ(A);
  SetFlagN(A);
}
void Cpu::LDX(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageY ||
         mode == Absolute || mode == IndexedAbsoluteY);

  X = memory_->Read(ExecuteAddressingMode(mode));
  SetFlagZ(X);
  SetFlagN(X);
}
void Cpu::LDY(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX);

  Y = memory_->Read(ExecuteAddressingMode(mode));
  SetFlagZ(Y);
  SetFlagN(Y);
}
void Cpu::LSR(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Accumulator || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX);

  uint8_t val;

  if (mode == Accumulator) {
    val = A;
    A = val / 2;
  } else {
    uint8_t addr = ExecuteAddressingMode(mode);
    val = memory_->Read(addr);
    memory_->Write(addr, val / 2);
  }

  SetStatusFlag(Carry, val >> 7 & 1);

  SetFlagN(val);
  SetFlagZ(val);
}
void Cpu::NOP(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);
}
void Cpu::ORA(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX ||
         mode == IndexedAbsoluteY || mode == IndexedIndirectX ||
         mode == IndexedIndirectY);

  A |= memory_->Read(ExecuteAddressingMode(mode));
  SetFlagN(A);
  SetFlagZ(A);
}
void Cpu::PHA(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  Push(A);
}
void Cpu::PHP(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  std::bitset<8> status = P;

  // 6502 bug
  status[Break] = 1;

  Push(status.to_ulong());
}
void Cpu::PLA(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  A = Pull();
}
void Cpu::PLP(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  P = Pull();
}
void Cpu::RLA(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::ROL(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Accumulator || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX);

  uint8_t val;
  bool old_carry;

  if (mode == Accumulator) {
    old_carry = (A >> 7) & 1;
    A <<= 1;
    A |= P[Carry];
    val = A;
  } else {
    uint16_t addr = ExecuteAddressingMode(mode);

    uint8_t M = memory_->Read(addr);
    old_carry = (M >> 7) & 1;
    M <<= 1;
    M |= P[Carry];
    val = M;
    memory_->Write(addr, M);
  }

  SetStatusFlag(Carry, old_carry);
  SetFlagN(val);
  SetFlagZ(val);
}
void Cpu::ROR(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Accumulator || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX);

  uint8_t val;
  bool old_carry;

  if (mode == Accumulator) {
    old_carry = A & 1;
    A >>= 1;
    A |= P[Carry] << 7;
    val = A;
  } else {
    uint16_t addr = ExecuteAddressingMode(mode);

    uint8_t M = memory_->Read(addr);
    old_carry = M & 1;
    M >>= 1;
    M |= P[Carry] << 7;
    val = M;
    memory_->Write(addr, M);
  }

  SetStatusFlag(Carry, old_carry);
  SetFlagN(val);
  SetFlagZ(val);
}
void Cpu::RRA(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::RTI(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  P = Pull();
  PC = Pull();
  PC |= Pull() << 8;
}
void Cpu::RTS(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  PC = Pull();
  PC |= Pull() << 8;
}
void Cpu::SAX(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::SBC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Immediate || mode == ZeroPage || mode == IndexedZeroPageX ||
         mode == Absolute || mode == IndexedAbsoluteX ||
         mode == IndexedAbsoluteY || mode == IndexedIndirectX ||
         mode == IndexedIndirectY);

  uint8_t M = memory_->Read(ExecuteAddressingMode(mode));
  uint16_t val = A + (M ^ 0xFF) + P[Carry];

  SetStatusFlag(Carry, val > 0xFF);

  // Overflow means the inputs are the same sign and the result is a different
  // sign, so we compare the MSB which is the sign bit in 2s complement
  SetStatusFlag(Overflow, ((A ^ M) >> 7) == 0 && (((A ^ val) >> 7) & 1) == 1);

  // Implicit cast from 16-bit to 8-bit to get truncated value
  A = val;

  SetFlagN(A);
  SetFlagZ(A);
}
void Cpu::SEC(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetStatusFlag(Carry, true);
}
void Cpu::SED(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetStatusFlag(Decimal, true);
}
void Cpu::SEI(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  SetStatusFlag(InterruptDisable, true);
}
void Cpu::SHX(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::SHY(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::SLO(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::SRE(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::STA(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == ZeroPage || mode == IndexedZeroPageX || mode == Absolute ||
         mode == IndexedAbsoluteX || mode == IndexedAbsoluteY ||
         mode == IndexedIndirectX || mode == IndexedIndirectY);

  memory_->Write(ExecuteAddressingMode(mode), A);
}
void Cpu::STP(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::STX(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == ZeroPage || mode == IndexedZeroPageY || mode == Absolute);

  memory_->Write(ExecuteAddressingMode(mode), X);
}
void Cpu::STY(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == ZeroPage || mode == IndexedZeroPageX || mode == Absolute);

  memory_->Write(ExecuteAddressingMode(mode), X);
}
void Cpu::TAS(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
void Cpu::TAX(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  X = A;
  SetFlagN(X);
  SetFlagZ(X);
}
void Cpu::TAY(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  Y = A;
  SetFlagN(Y);
  SetFlagZ(Y);
}
void Cpu::TSX(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  X = S;
  SetFlagN(X);
  SetFlagZ(X);
}
void Cpu::TXA(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  A = X;
  SetFlagN(A);
  SetFlagZ(A);
}
void Cpu::TXS(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);
  S = X;
}
void Cpu::TYA(const AddressingMode mode) {
  spdlog::info("{0}", __FUNCTION__);
  assert(mode == Implicit);

  A = Y;
  SetFlagN(A);
  SetFlagZ(A);
}
void Cpu::XAA(const AddressingMode mode) {
  spdlog::info("{0}:{1}", __FUNCTION__, mode);
}
