#include "cpu.hh"

Cpu::Cpu(CpuMemory* memory) : memory_(memory), PC(0xFFFC), A(0), X(0), Y(0) {
  P.reset();
}

Cpu::~Cpu() { delete memory_; }

void Cpu::Exec(uint8_t opcode) {
  switch (opcode) {
    case 0:
      Cpu::BRK();
      break;
    case 1:
      Cpu::ORA();
      break;
    case 2:
      Cpu::STP();
      break;
    case 3:
      Cpu::SLO();
      break;
    case 4:
      Cpu::NOP();
      break;
    case 5:
      Cpu::ORA();
      break;
    case 6:
      Cpu::ASL();
      break;
    case 7:
      Cpu::SLO();
      break;
    case 8:
      Cpu::PHP();
      break;
    case 9:
      Cpu::ORA();
      break;
    case 10:
      Cpu::ASL();
      break;
    case 11:
      Cpu::ANC();
      break;
    case 12:
      Cpu::NOP();
      break;
    case 13:
      Cpu::ORA();
      break;
    case 14:
      Cpu::ASL();
      break;
    case 15:
      Cpu::SLO();
      break;
    case 16:
      Cpu::BPL();
      break;
    case 17:
      Cpu::ORA();
      break;
    case 18:
      Cpu::STP();
      break;
    case 19:
      Cpu::SLO();
      break;
    case 20:
      Cpu::NOP();
      break;
    case 21:
      Cpu::ORA();
      break;
    case 22:
      Cpu::ASL();
      break;
    case 23:
      Cpu::SLO();
      break;
    case 24:
      Cpu::CLC();
      break;
    case 25:
      Cpu::ORA();
      break;
    case 26:
      Cpu::NOP();
      break;
    case 27:
      Cpu::SLO();
      break;
    case 28:
      Cpu::NOP();
      break;
    case 29:
      Cpu::ORA();
      break;
    case 30:
      Cpu::ASL();
      break;
    case 31:
      Cpu::SLO();
      break;
    case 32:
      Cpu::JSR();
      break;
    case 33:
      Cpu::AND();
      break;
    case 34:
      Cpu::STP();
      break;
    case 35:
      Cpu::RLA();
      break;
    case 36:
      Cpu::BIT();
      break;
    case 37:
      Cpu::AND();
      break;
    case 38:
      Cpu::ROL();
      break;
    case 39:
      Cpu::RLA();
      break;
    case 40:
      Cpu::PLP();
      break;
    case 41:
      Cpu::AND();
      break;
    case 42:
      Cpu::ROL();
      break;
    case 43:
      Cpu::ANC();
      break;
    case 44:
      Cpu::BIT();
      break;
    case 45:
      Cpu::AND();
      break;
    case 46:
      Cpu::ROL();
      break;
    case 47:
      Cpu::RLA();
      break;
    case 48:
      Cpu::BMI();
      break;
    case 49:
      Cpu::AND();
      break;
    case 50:
      Cpu::STP();
      break;
    case 51:
      Cpu::RLA();
      break;
    case 52:
      Cpu::NOP();
      break;
    case 53:
      Cpu::AND();
      break;
    case 54:
      Cpu::ROL();
      break;
    case 55:
      Cpu::RLA();
      break;
    case 56:
      Cpu::SEC();
      break;
    case 57:
      Cpu::AND();
      break;
    case 58:
      Cpu::NOP();
      break;
    case 59:
      Cpu::RLA();
      break;
    case 60:
      Cpu::NOP();
      break;
    case 61:
      Cpu::AND();
      break;
    case 62:
      Cpu::ROL();
      break;
    case 63:
      Cpu::RLA();
      break;
    case 64:
      Cpu::RTI();
      break;
    case 65:
      Cpu::EOR();
      break;
    case 66:
      Cpu::STP();
      break;
    case 67:
      Cpu::SRE();
      break;
    case 68:
      Cpu::NOP();
      break;
    case 69:
      Cpu::EOR();
      break;
    case 70:
      Cpu::LSR();
      break;
    case 71:
      Cpu::SRE();
      break;
    case 72:
      Cpu::PHA();
      break;
    case 73:
      Cpu::EOR();
      break;
    case 74:
      Cpu::LSR();
      break;
    case 75:
      Cpu::ALR();
      break;
    case 76:
      Cpu::JMP();
      break;
    case 77:
      Cpu::EOR();
      break;
    case 78:
      Cpu::LSR();
      break;
    case 79:
      Cpu::SRE();
      break;
    case 80:
      Cpu::BVC();
      break;
    case 81:
      Cpu::EOR();
      break;
    case 82:
      Cpu::STP();
      break;
    case 83:
      Cpu::SRE();
      break;
    case 84:
      Cpu::NOP();
      break;
    case 85:
      Cpu::EOR();
      break;
    case 86:
      Cpu::LSR();
      break;
    case 87:
      Cpu::SRE();
      break;
    case 88:
      Cpu::CLI();
      break;
    case 89:
      Cpu::EOR();
      break;
    case 90:
      Cpu::NOP();
      break;
    case 91:
      Cpu::SRE();
      break;
    case 92:
      Cpu::NOP();
      break;
    case 93:
      Cpu::EOR();
      break;
    case 94:
      Cpu::LSR();
      break;
    case 95:
      Cpu::SRE();
      break;
    case 96:
      Cpu::RTS();
      break;
    case 97:
      Cpu::ADC();
      break;
    case 98:
      Cpu::STP();
      break;
    case 99:
      Cpu::RRA();
      break;
    case 100:
      Cpu::NOP();
      break;
    case 101:
      Cpu::ADC();
      break;
    case 102:
      Cpu::ROR();
      break;
    case 103:
      Cpu::RRA();
      break;
    case 104:
      Cpu::PLA();
      break;
    case 105:
      Cpu::ADC();
      break;
    case 106:
      Cpu::ROR();
      break;
    case 107:
      Cpu::ARR();
      break;
    case 108:
      Cpu::JMP();
      break;
    case 109:
      Cpu::ADC();
      break;
    case 110:
      Cpu::ROR();
      break;
    case 111:
      Cpu::RRA();
      break;
    case 112:
      Cpu::BVS();
      break;
    case 113:
      Cpu::ADC();
      break;
    case 114:
      Cpu::STP();
      break;
    case 115:
      Cpu::RRA();
      break;
    case 116:
      Cpu::NOP();
      break;
    case 117:
      Cpu::ADC();
      break;
    case 118:
      Cpu::ROR();
      break;
    case 119:
      Cpu::RRA();
      break;
    case 120:
      Cpu::SEI();
      break;
    case 121:
      Cpu::ADC();
      break;
    case 122:
      Cpu::NOP();
      break;
    case 123:
      Cpu::RRA();
      break;
    case 124:
      Cpu::NOP();
      break;
    case 125:
      Cpu::ADC();
      break;
    case 126:
      Cpu::ROR();
      break;
    case 127:
      Cpu::RRA();
      break;
    case 128:
      Cpu::NOP();
      break;
    case 129:
      Cpu::STA();
      break;
    case 130:
      Cpu::NOP();
      break;
    case 131:
      Cpu::SAX();
      break;
    case 132:
      Cpu::STY();
      break;
    case 133:
      Cpu::STA();
      break;
    case 134:
      Cpu::STX();
      break;
    case 135:
      Cpu::SAX();
      break;
    case 136:
      Cpu::DEY();
      break;
    case 137:
      Cpu::NOP();
      break;
    case 138:
      Cpu::TXA();
      break;
    case 139:
      Cpu::XAA();
      break;
    case 140:
      Cpu::STY();
      break;
    case 141:
      Cpu::STA();
      break;
    case 142:
      Cpu::STX();
      break;
    case 143:
      Cpu::SAX();
      break;
    case 144:
      Cpu::BCC();
      break;
    case 145:
      Cpu::STA();
      break;
    case 146:
      Cpu::STP();
      break;
    case 147:
      Cpu::AHX();
      break;
    case 148:
      Cpu::STY();
      break;
    case 149:
      Cpu::STA();
      break;
    case 150:
      Cpu::STX();
      break;
    case 151:
      Cpu::SAX();
      break;
    case 152:
      Cpu::TYA();
      break;
    case 153:
      Cpu::STA();
      break;
    case 154:
      Cpu::TXS();
      break;
    case 155:
      Cpu::TAS();
      break;
    case 156:
      Cpu::SHY();
      break;
    case 157:
      Cpu::STA();
      break;
    case 158:
      Cpu::SHX();
      break;
    case 159:
      Cpu::AHX();
      break;
    case 160:
      Cpu::LDY();
      break;
    case 161:
      Cpu::LDA();
      break;
    case 162:
      Cpu::LDX();
      break;
    case 163:
      Cpu::LAX();
      break;
    case 164:
      Cpu::LDY();
      break;
    case 165:
      Cpu::LDA();
      break;
    case 166:
      Cpu::LDX();
      break;
    case 167:
      Cpu::LAX();
      break;
    case 168:
      Cpu::TAY();
      break;
    case 169:
      Cpu::LDA();
      break;
    case 170:
      Cpu::TAX();
      break;
    case 171:
      Cpu::LAX();
      break;
    case 172:
      Cpu::LDY();
      break;
    case 173:
      Cpu::LDA();
      break;
    case 174:
      Cpu::LDX();
      break;
    case 175:
      Cpu::LAX();
      break;
    case 176:
      Cpu::BCS();
      break;
    case 177:
      Cpu::LDA();
      break;
    case 178:
      Cpu::STP();
      break;
    case 179:
      Cpu::LAX();
      break;
    case 180:
      Cpu::LDY();
      break;
    case 181:
      Cpu::LDA();
      break;
    case 182:
      Cpu::LDX();
      break;
    case 183:
      Cpu::LAX();
      break;
    case 184:
      Cpu::CLV();
      break;
    case 185:
      Cpu::LDA();
      break;
    case 186:
      Cpu::TSX();
      break;
    case 187:
      Cpu::LAS();
      break;
    case 188:
      Cpu::LDY();
      break;
    case 189:
      Cpu::LDA();
      break;
    case 190:
      Cpu::LDX();
      break;
    case 191:
      Cpu::LAX();
      break;
    case 192:
      Cpu::CPY();
      break;
    case 193:
      Cpu::CMP();
      break;
    case 194:
      Cpu::NOP();
      break;
    case 195:
      Cpu::DCP();
      break;
    case 196:
      Cpu::CPY();
      break;
    case 197:
      Cpu::CMP();
      break;
    case 198:
      Cpu::DEC();
      break;
    case 199:
      Cpu::DCP();
      break;
    case 200:
      Cpu::INY();
      break;
    case 201:
      Cpu::CMP();
      break;
    case 202:
      Cpu::DEX();
      break;
    case 203:
      Cpu::AXS();
      break;
    case 204:
      Cpu::CPY();
      break;
    case 205:
      Cpu::CMP();
      break;
    case 206:
      Cpu::DEC();
      break;
    case 207:
      Cpu::DCP();
      break;
    case 208:
      Cpu::BNE();
      break;
    case 209:
      Cpu::CMP();
      break;
    case 210:
      Cpu::STP();
      break;
    case 211:
      Cpu::DCP();
      break;
    case 212:
      Cpu::NOP();
      break;
    case 213:
      Cpu::CMP();
      break;
    case 214:
      Cpu::DEC();
      break;
    case 215:
      Cpu::DCP();
      break;
    case 216:
      Cpu::CLD();
      break;
    case 217:
      Cpu::CMP();
      break;
    case 218:
      Cpu::NOP();
      break;
    case 219:
      Cpu::DCP();
      break;
    case 220:
      Cpu::NOP();
      break;
    case 221:
      Cpu::CMP();
      break;
    case 222:
      Cpu::DEC();
      break;
    case 223:
      Cpu::DCP();
      break;
    case 224:
      Cpu::CPX();
      break;
    case 225:
      Cpu::SBC();
      break;
    case 226:
      Cpu::NOP();
      break;
    case 227:
      Cpu::ISC();
      break;
    case 228:
      Cpu::CPX();
      break;
    case 229:
      Cpu::SBC();
      break;
    case 230:
      Cpu::INC();
      break;
    case 231:
      Cpu::ISC();
      break;
    case 232:
      Cpu::INX();
      break;
    case 233:
      Cpu::SBC();
      break;
    case 234:
      Cpu::NOP();
      break;
    case 235:
      Cpu::SBC();
      break;
    case 236:
      Cpu::CPX();
      break;
    case 237:
      Cpu::SBC();
      break;
    case 238:
      Cpu::INC();
      break;
    case 239:
      Cpu::ISC();
      break;
    case 240:
      Cpu::BEQ();
      break;
    case 241:
      Cpu::SBC();
      break;
    case 242:
      Cpu::STP();
      break;
    case 243:
      Cpu::ISC();
      break;
    case 244:
      Cpu::NOP();
      break;
    case 245:
      Cpu::SBC();
      break;
    case 246:
      Cpu::INC();
      break;
    case 247:
      Cpu::ISC();
      break;
    case 248:
      Cpu::SED();
      break;
    case 249:
      Cpu::SBC();
      break;
    case 250:
      Cpu::NOP();
      break;
    case 251:
      Cpu::ISC();
      break;
    case 252:
      Cpu::NOP();
      break;
    case 253:
      Cpu::SBC();
      break;
    case 254:
      Cpu::INC();
      break;
    case 255:
      Cpu::ISC();
      break;
  }
}
