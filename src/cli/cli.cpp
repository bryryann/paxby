// cli.cpp
//
// Settings and configurations used by the cli command parsing.
// Also define helper functions.

#include "cli/cli.h"

#include <iostream>

namespace cli {

struct option options[] = {
    {"help",    no_argument,       nullptr, 'h'},
    {"verbose", no_argument,       nullptr, 'v'},
    {nullptr,   0,                 nullptr,  0 }
};

void print_help() {
    std::cout << "usage: paxby [OPTION]... [ARG]...\n"
              << "options:\n"
              << " -h, --help    Display this help and exit.\n";
}

}
