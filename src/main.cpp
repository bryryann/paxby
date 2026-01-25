#include "core/core.h"
#include "cli/command.h"

#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt_long(argc, argv, "h", cli::options, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                cli::print_help();
                return 0;
            default:
                return 1;
        }
    }

    core::run();
    return 0;
}
