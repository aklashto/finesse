#include <gtkmm.h>
#include <spdlog/spdlog.h>

#include <iostream>

#include "nes.hh"

inline bool ends_with(const std::string &input, const std::string &suffix) {
  size_t suffix_length = suffix.length();
  size_t input_length = input.length();
  if (suffix_length > input_length) {
    return false;
  }
  return !(input.compare(input_length - suffix_length, suffix_length, suffix));
}

int main(int argc, char **argv) {
  if (argc != 2) {
    spdlog::error("{} takes an input file as argument.", argv[0]);
    spdlog::error("  Usage: {} <filename>.nes", argv[0]);
    return -1;
  }

  std::string input_name(argv[1]);
  if (!ends_with(input_name, ".nes")) {
    spdlog::error("Argument must be a file name with a .nes extension");
    return -2;
  }

  std::ifstream infile(input_name, std::ios::in | std::ios::binary);

  if (!infile.is_open()) {
    spdlog::error("Failed to open test file {}", input_name);
    return -3;
  }

  Nes nes;
  nes.ReadInputFile(infile);

  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  Gtk::Window window;
  window.set_default_size(200, 200);

  return app->run(window);

  return 0;
}
