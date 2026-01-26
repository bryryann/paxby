#include "cli/command.h"
#include "cli/command_parser.h"

#include <getopt.h>

namespace cli {

CommandResult parse_command(int argc, char **argv) {
    int opt;

    while ((opt = getopt_long(argc, argv, "h", options, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return CommandResult::ExitSuccess;
            default:
                return CommandResult::ExitFailure;
        }
    }

    return CommandResult::Run;
}

}
