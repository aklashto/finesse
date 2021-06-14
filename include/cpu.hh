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
    Break = 4,
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

  // Stack operations
  uint8_t Pull();
  void Push(const uint8_t val);

  // Status flag operations
  void SetStatusFlag(const StatusFlag flag, const bool condition);
  void SetFlagZ(const uint8_t val);
  void SetFlagN(const uint8_t val);

  // Instruction helper methods
  uint16_t ExecuteAddressingMode(const AddressingMode mode);
  void PerformAdd(const uint8_t val);

  // CPU instructions
  void ADC(const AddressingMode mode = Implicit);
  void AHX(const AddressingMode mode = Implicit);
  void ALR(const AddressingMode mode = Implicit);
  void ANC(const AddressingMode mode = Implicit);
  void AND(const AddressingMode mode = Implicit);
  void ARR(const AddressingMode mode = Implicit);
  void ASL(const AddressingMode mode = Implicit);
  void AXS(const AddressingMode mode = Implicit);
  void BCC(const AddressingMode mode = Implicit);
  void BCS(const AddressingMode mode = Implicit);
  void BEQ(const AddressingMode mode = Implicit);
  void BIT(const AddressingMode mode = Implicit);
  void BMI(const AddressingMode mode = Implicit);
  void BNE(const AddressingMode mode = Implicit);
  void BPL(const AddressingMode mode = Implicit);
  void BRK(const AddressingMode mode = Implicit);
  void BVC(const AddressingMode mode = Implicit);
  void BVS(const AddressingMode mode = Implicit);
  void CLC(const AddressingMode mode = Implicit);
  void CLD(const AddressingMode mode = Implicit);
  void CLI(const AddressingMode mode = Implicit);
  void CLV(const AddressingMode mode = Implicit);
  void CMP(const AddressingMode mode = Implicit);
  void CPX(const AddressingMode mode = Implicit);
  void CPY(const AddressingMode mode = Implicit);
  void DCP(const AddressingMode mode = Implicit);
  void DEC(const AddressingMode mode = Implicit);
  void DEX(const AddressingMode mode = Implicit);
  void DEY(const AddressingMode mode = Implicit);
  void EOR(const AddressingMode mode = Implicit);
  void INC(const AddressingMode mode = Implicit);
  void INX(const AddressingMode mode = Implicit);
  void INY(const AddressingMode mode = Implicit);
  void ISC(const AddressingMode mode = Implicit);
  void JMP(const AddressingMode mode = Implicit);
  void JSR(const AddressingMode mode = Implicit);
  void LAS(const AddressingMode mode = Implicit);
  void LAX(const AddressingMode mode = Implicit);
  void LDA(const AddressingMode mode = Implicit);
  void LDX(const AddressingMode mode = Implicit);
  void LDY(const AddressingMode mode = Implicit);
  void LSR(const AddressingMode mode = Implicit);
  void NOP(const AddressingMode mode = Implicit);
  void ORA(const AddressingMode mode = Implicit);
  void PHA(const AddressingMode mode = Implicit);
  void PHP(const AddressingMode mode = Implicit);
  void PLA(const AddressingMode mode = Implicit);
  void PLP(const AddressingMode mode = Implicit);
  void RLA(const AddressingMode mode = Implicit);
  void ROL(const AddressingMode mode = Implicit);
  void ROR(const AddressingMode mode = Implicit);
  void RRA(const AddressingMode mode = Implicit);
  void RTI(const AddressingMode mode = Implicit);
  void RTS(const AddressingMode mode = Implicit);
  void SAX(const AddressingMode mode = Implicit);
  void SBC(const AddressingMode mode = Implicit);
  void SEC(const AddressingMode mode = Implicit);
  void SED(const AddressingMode mode = Implicit);
  void SEI(const AddressingMode mode = Implicit);
  void SHX(const AddressingMode mode = Implicit);
  void SHY(const AddressingMode mode = Implicit);
  void SLO(const AddressingMode mode = Implicit);
  void SRE(const AddressingMode mode = Implicit);
  void STA(const AddressingMode mode = Implicit);
  void STP(const AddressingMode mode = Implicit);
  void STX(const AddressingMode mode = Implicit);
  void STY(const AddressingMode mode = Implicit);
  void TAS(const AddressingMode mode = Implicit);
  void TAX(const AddressingMode mode = Implicit);
  void TAY(const AddressingMode mode = Implicit);
  void TSX(const AddressingMode mode = Implicit);
  void TXA(const AddressingMode mode = Implicit);
  void TXS(const AddressingMode mode = Implicit);
  void TYA(const AddressingMode mode = Implicit);
  void XAA(const AddressingMode mode = Implicit);

  void Exec(const uint8_t opcode);

 public:
  Cpu(CpuMemory* memory);
  ~Cpu();

  void Run();
};

#endif
