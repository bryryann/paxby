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
