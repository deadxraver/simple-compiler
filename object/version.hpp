#pragma once
#pragma packed

#include <string>

constexpr uint8_t VERSION[3] = {0, 0, 1};

#define VERSION_STR \
  (std::to_string(VERSION[0]) + "." \
  + std::to_string(VERSION[1]) + "." \
  + std::to_string(VERSION[2]))

