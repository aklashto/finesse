#include <iostream>
#include "nes.hh"

Nes::Nes() {}
Nes::~Nes() {}
void Nes::ReadInputFile(std::ifstream & infile) {
    if (infile.peek() == std::ifstream::traits_type::eof()) return;
    std::cout << "Non-empty .nes file provided!" << std::endl;
}
