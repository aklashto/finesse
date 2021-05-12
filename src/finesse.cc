#include <iostream>
#include "nes.hh"

inline bool ends_with(const std::string & input, const std::string & suffix) {
    size_t suffix_length = suffix.length();
    size_t input_length = input.length();
    if (suffix_length > input_length) {
        return false;
    }
    return !(input.compare(input_length - suffix_length, suffix_length, suffix));
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << argv[0] <<  " takes an input file as an argument.\n"
            "Usage: " << argv[0] << " <filename>.nes" << std::endl;
        return -1;
    }

    std::string input_name(argv[1]);
    if (!ends_with(input_name, ".nes")) {
        std::cerr << "First argument must be a file name with a .nes extension"
                  << std::endl;
        return -2;
    }

    std::ifstream infile(input_name, std::ios::in | std::ios::binary);

    if (!infile.is_open()) {
        std::cerr << "Failed to open test file" << std::endl;
        return -3;
    }

    Nes nes;
    nes.ReadInputFile(infile);

    return 0;
}
