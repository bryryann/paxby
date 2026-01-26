#include "cli/command.h"
#include "cli/command_parser.h"

#include <getopt.h>

namespace cli {

CommandResult parse_command(int argc, char **argv, core::Context &ctx) {
    optind = 1;

    int opt;
    while ((opt = getopt_long(argc, argv, "hv", options, nullptr)) != -1) {
        switch (opt) {
            case 'h':
                ctx.show_help = true;
                print_help();
                return CommandResult::ExitSuccess;

            case 'v':
                ctx.verbose = true;
                break;

            default:
                return CommandResult::ExitFailure;
        }
    }

    return CommandResult::Run;
}

}
