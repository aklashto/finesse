# This file is based on sample configuration from:
# https://github.com/tiernemi/meson-sample-project

project('finesse', 'cpp',
  version : '0.1',
  license : 'MIT',
  default_options : ['warning_level=3',
                     'cpp_std=c++17'])

# Variables tracking sources and libraries
library_path = []
src = []
headers = []
tests = []
deps = []

inc = [include_directories('include')]

spdlog = subproject('spdlog')
catch2 = subproject('catch2')

subdir('include')
subdir('src')

finesse_bin = executable('finesse_bin',
  src,
  include_directories : inc,
  dependencies : deps)

dirs_to_format = [src, tests, headers]

# This adds the clang-format file to the build directory
configure_file(input : '.clang-format',
               output : '.clang-format',
               copy: true)
run_target('format',
           command : ['clang-format','-i','-style=file', dirs_to_format])

# This adds clang-tidy support
configure_file(input : '.clang-tidy',
               output : '.clang-tidy',
               copy : true)
run_target('tidy',
           command : ['clang-tidy','-fix', dirs_to_format,'-format-style=file', '-p='+ meson.build_root()])
