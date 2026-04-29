#pragma once

#include <string>
#include <stdexcept>

struct cl_args {
  std::string file_path;
  std::string output_path;
  bool verbose;
  bool help_only;
  bool version_only;
  cl_args(int argc, char* argv[]) :
    verbose(false),
    help_only(false),
    version_only(false)
  {
    bool found_src = false;
    bool found_out = false;
    for (int i = 1; i < argc; ++i) {
      if (std::string("-o") == argv[i]) {
        if (found_out)
          throw std::invalid_argument("Only one `-o` expected");
        found_out = true;
        output_path = argv[++i];
      }
      else if (
        std::string("-h") == argv[i] ||
        std::string("--help") == argv[i]
      ) {
        help_only = true;
        break;
      }
      else if (
        std::string("--version") == argv[i]
      ) {
        version_only = true;
        break;
      }
      else if (
        std::string("-v") == argv[i] ||
        std::string("--verbose") == argv[i]
      ) {
        verbose = true;
      }
      else if (argv[i][0] == '-') {
        throw std::invalid_argument(std::string("Unknown flag: ") + argv[i]);
      }
      else {
        if (found_src) {
          throw std::invalid_argument("Input file redefined");
        }
        found_src = true;
        file_path = argv[i];
      }
    }
    if (!help_only && !version_only) {
      if (!found_src)
        throw std::invalid_argument("Input file missing");
      if (!found_out)
        output_path = "./a.out";
    }
  }
};
