#pragma once

#include <fstream>
#include <string>

namespace io {

void writestring(std::ofstream& out, const std::string& str);

std::string readstring(std::ifstream& in);

}

