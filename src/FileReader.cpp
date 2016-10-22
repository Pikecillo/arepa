#include <assert.h>
#include <fstream>

#include "FileReader.h"

std::string FileReader::read_text_file(const std::string &filename) {
    std::ifstream input(filename.c_str(), std::ios::in);
    std::string text = "", line;
    
    assert(input.good());

    while(!input.eof()) {
	getline(input, line);
	text += (line + '\n');
    }
    
    return text;
}
