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

  uint8_t Pop();
  void Push(uint8_t val);

  void ADC(AddressingMode mode = Implicit);
  void AHX(AddressingMode mode = Implicit);
  void ALR(AddressingMode mode = Implicit);
  void ANC(AddressingMode mode = Implicit);
  void AND(AddressingMode mode = Implicit);
  void ARR(AddressingMode mode = Implicit);
  void ASL(AddressingMode mode = Implicit);
  void AXS(AddressingMode mode = Implicit);
  void BCC(AddressingMode mode = Implicit);
  void BCS(AddressingMode mode = Implicit);
  void BEQ(AddressingMode mode = Implicit);
  void BIT(AddressingMode mode = Implicit);
  void BMI(AddressingMode mode = Implicit);
  void BNE(AddressingMode mode = Implicit);
  void BPL(AddressingMode mode = Implicit);
  void BRK(AddressingMode mode = Implicit);
  void BVC(AddressingMode mode = Implicit);
  void BVS(AddressingMode mode = Implicit);
  void CLC(AddressingMode mode = Implicit);
  void CLD(AddressingMode mode = Implicit);
  void CLI(AddressingMode mode = Implicit);
  void CLV(AddressingMode mode = Implicit);
  void CMP(AddressingMode mode = Implicit);
  void CPX(AddressingMode mode = Implicit);
  void CPY(AddressingMode mode = Implicit);
  void DCP(AddressingMode mode = Implicit);
  void DEC(AddressingMode mode = Implicit);
  void DEX(AddressingMode mode = Implicit);
  void DEY(AddressingMode mode = Implicit);
  void EOR(AddressingMode mode = Implicit);
  void INC(AddressingMode mode = Implicit);
  void INX(AddressingMode mode = Implicit);
  void INY(AddressingMode mode = Implicit);
  void ISC(AddressingMode mode = Implicit);
  void JMP(AddressingMode mode = Implicit);
  void JSR(AddressingMode mode = Implicit);
  void LAS(AddressingMode mode = Implicit);
  void LAX(AddressingMode mode = Implicit);
  void LDA(AddressingMode mode = Implicit);
  void LDX(AddressingMode mode = Implicit);
  void LDY(AddressingMode mode = Implicit);
  void LSR(AddressingMode mode = Implicit);
  void NOP(AddressingMode mode = Implicit);
  void ORA(AddressingMode mode = Implicit);
  void PHA(AddressingMode mode = Implicit);
  void PHP(AddressingMode mode = Implicit);
  void PLA(AddressingMode mode = Implicit);
  void PLP(AddressingMode mode = Implicit);
  void RLA(AddressingMode mode = Implicit);
  void ROL(AddressingMode mode = Implicit);
  void ROR(AddressingMode mode = Implicit);
  void RRA(AddressingMode mode = Implicit);
  void RTI(AddressingMode mode = Implicit);
  void RTS(AddressingMode mode = Implicit);
  void SAX(AddressingMode mode = Implicit);
  void SBC(AddressingMode mode = Implicit);
  void SEC(AddressingMode mode = Implicit);
  void SED(AddressingMode mode = Implicit);
  void SEI(AddressingMode mode = Implicit);
  void SHX(AddressingMode mode = Implicit);
  void SHY(AddressingMode mode = Implicit);
  void SLO(AddressingMode mode = Implicit);
  void SRE(AddressingMode mode = Implicit);
  void STA(AddressingMode mode = Implicit);
  void STP(AddressingMode mode = Implicit);
  void STX(AddressingMode mode = Implicit);
  void STY(AddressingMode mode = Implicit);
  void TAS(AddressingMode mode = Implicit);
  void TAX(AddressingMode mode = Implicit);
  void TAY(AddressingMode mode = Implicit);
  void TSX(AddressingMode mode = Implicit);
  void TXA(AddressingMode mode = Implicit);
  void TXS(AddressingMode mode = Implicit);
  void TYA(AddressingMode mode = Implicit);
  void XAA(AddressingMode mode = Implicit);

  void Exec(uint8_t opcode);

 public:
  Cpu(CpuMemory* memory);
  ~Cpu();

  void Run();
};

#endif
