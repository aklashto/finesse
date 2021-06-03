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
    ZeroPageX,
    ZeroPageY,
    AbsoluteX,
    AbsoluteY,
    IndirectX,
    IndirectY
  };

  void ADC() {}
  void AHX() {}
  void ALR() {}
  void ANC() {}
  void AND() {}
  void ARR() {}
  void ASL() {}
  void AXS() {}
  void BCC() {}
  void BCS() {}
  void BEQ() {}
  void BIT() {}
  void BMI() {}
  void BNE() {}
  void BPL() {}
  void BRK() {}
  void BVC() {}
  void BVS() {}
  void CLC() {}
  void CLD() {}
  void CLI() {}
  void CLV() {}
  void CMP() {}
  void CPX() {}
  void CPY() {}
  void DCP() {}
  void DEC() {}
  void DEX() {}
  void DEY() {}
  void EOR() {}
  void INC() {}
  void INX() {}
  void INY() {}
  void ISC() {}
  void JMP() {}
  void JSR() {}
  void LAS() {}
  void LAX() {}
  void LDA() {}
  void LDX() {}
  void LDY() {}
  void LSR() {}
  void NOP() {}
  void ORA() {}
  void PHA() {}
  void PHP() {}
  void PLA() {}
  void PLP() {}
  void RLA() {}
  void ROL() {}
  void ROR() {}
  void RRA() {}
  void RTI() {}
  void RTS() {}
  void SAX() {}
  void SBC() {}
  void SEC() {}
  void SED() {}
  void SEI() {}
  void SHX() {}
  void SHY() {}
  void SLO() {}
  void SRE() {}
  void STA() {}
  void STP() {}
  void STX() {}
  void STY() {}
  void TAS() {}
  void TAX() {}
  void TAY() {}
  void TSX() {}
  void TXA() {}
  void TXS() {}
  void TYA() {}
  void XAA() {}

  void Exec(uint8_t opcode);

  std::array<AddressingMode, 256> addr_mode_map_;

 public:
  Cpu(CpuMemory* memory);
  ~Cpu();
};

#endif
