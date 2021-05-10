#include "nes.hh"

namespace finesse {
    Nes::Nes() {}
    Nes::~Nes() {}
    void Nes::ReadInputFile(std::ifstream & infile) {
        if (infile.peek() == std::ifstream::traits_type::eof()) return;
    }
}
