#include "core/core.h"

#include <iostream>
#include <getopt.h>

void print_help() {
    std::cout << "Usage: paxby [OPTION]... [ARG]...\n"
              << "Options:\n"
              << " -h, --help    Display this help and exit.\n";
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt_long(argc, argv, "hn:", core::long_options, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            default:
                return 1;
        }
    }

    core::run();
    return 0;
}
