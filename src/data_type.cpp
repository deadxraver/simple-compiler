#include "data_type.hpp"

#include <stdexcept>

std::ostream& operator<<(std::ostream& os, DataType dt) {
  switch (dt) {
    case dtUnknown: {
      os << "Unknown";
      break;
    }
    case dtNumber: {
      os << "Number";
      break;
    }
    case dtString: {
      os << "String";
      break;
    }
    case dtBool: {
      os << "Bool";
      break;
    }
    default: {
      throw std::out_of_range("DataType " + std::to_string(static_cast<int>(dt)) + " undefined");
    }
  }

  return os;
}
