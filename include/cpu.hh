#ifndef CPU_HH
#define CPU_HH

#include <spdlog/spdlog.h>

#include <bitset>
#include <cstdint>

#include "cpu_memory.hh"

/**
 * The NES CPU
 */
class Cpu {
 private:
  CpuMemory* memory_;
  uint16_t PC;
  uint8_t S;
  uint8_t A;
  uint8_t X;
  uint8_t Y;
  std::bitset<8> P;

  // Used to index into status register P
  enum StatusFlag {
    Carry = 0,
    Zero = 1,
    InterruptDisable = 2,
    Decimal = 3,
    Overflow = 6,
    Negative = 7
  };

  enum AddressingMode {
    IndexedZeroPageX,  // d,x
    IndexedZeroPageY,  // d,y
    IndexedAbsoluteX,  // a,x
    IndexedAbsoluteY,  // a,y
    IndexedIndirectX,  // (d,x)
    IndexedIndirectY,  // (d),y
    Accumulator,       // A
    Immediate,         // #i
    ZeroPage,          // d
    Absolute,          // a
    Relative,          // label
    Indirect,          // (a)
    Implicit           //
  };

  void ADC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void AHX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ALR(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ANC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void AND(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ARR(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ASL(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void AXS(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BCC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BCS(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BEQ(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BIT(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BMI(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BNE(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BPL(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BRK(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BVC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void BVS(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void CLC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void CLD(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void CLI(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void CLV(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void CMP(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void CPX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void CPY(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void DCP(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void DEC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void DEX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void DEY(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void EOR(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void INC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void INX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void INY(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ISC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void JMP(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void JSR(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void LAS(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void LAX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void LDA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void LDX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void LDY(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void LSR(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void NOP(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ORA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void PHA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void PHP(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void PLA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void PLP(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void RLA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ROL(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void ROR(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void RRA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void RTI(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void RTS(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SAX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SBC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SEC(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SED(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SEI(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SHX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SHY(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SLO(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void SRE(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void STA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void STP(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void STX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void STY(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void TAS(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void TAX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void TAY(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void TSX(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void TXA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void TXS(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void TYA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }
  void XAA(AddressingMode mode = Implicit) { spdlog::info("Mode: {0}", mode); }

  void Exec(uint8_t opcode);

 public:
  Cpu(CpuMemory* memory);
  ~Cpu();
};

#endif
