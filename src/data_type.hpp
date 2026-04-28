#pragma once

#include <iostream>

enum DataType {
  dtUnknown = 0,
  dtNumber,
  dtString,
  dtBool,
};

std::ostream& operator<<(std::ostream& os, DataType dt);
