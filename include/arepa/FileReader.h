#pragma once

#include <string>

namespace arepa {

class FileReader {
  public:
    static std::string read_text_file(const std::string &filename);
};

} // namespace arepa
