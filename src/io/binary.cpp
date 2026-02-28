#include "io/binary.h"

#include <cstdint>

namespace io {

// Writes a string to a binary file stream.
// Format: [8 bytes: string size][N bytes: string data]
void writestring(std::ostream& out, const std::string& str) {
    uint64_t size = str.size();

    // Write the size of the string to the file first.
    // reinterpret_cast converts the address of size to a char pointer
    // because write() expects a pointer to raw bytes.
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));

    // Write the actual string data (raw bytes, no null terminator).
    // str.data() returns a pointer to the character buffer.
    out.write(str.data(), size);
}

// Reads a string from a binary file stream.
// Format: [8 bytes: string size][N bytes: string data]
std::string readstring(std::ifstream& in) {
    uint64_t size;

    // Read the first 8 bytes to get the size of the string.
    in.read(reinterpret_cast<char*>(&size), sizeof(size));

    std::string str(size, '\0');

    in.read(str.data(), size);

    return str;
}

}
