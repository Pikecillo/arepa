#include <fstream>

#include <arepa/Common.h>
#include <arepa/FileReader.h>

namespace arepa {
std::string FileReader::read_text_file(const std::string &filename) {
    std::ifstream input(filename.c_str(), std::ios::in);
    std::string text = "", line;

    AREPA_ASSERT(input.good());

    while (!input.eof()) {
        getline(input, line);
        text += (line + '\n');
    }

    return text;
}
} // namespace arepa
