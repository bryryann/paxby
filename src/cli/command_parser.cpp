// command_parser.cpp
//
// Parse commands, subcommands, options and arguments.
// Create context object and decide whether to run or exit application.

#include "cli/cli.h"
#include "cli/command_parser.h"

#include <iostream>
#include <getopt.h>

namespace cli {

// Parse user command.
//
// Extract options, subcommands and arguments, creating appropriate context object
// and deciding whether to exit or run application.
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

    if (optind >= argc) {
        std::cerr << "No command specified\n";
        return CommandResult::ExitFailure;
    }

    std::string cmd = optind[argv];

    if (cmd == "init") {
        ctx.command = core::Command::Init;

        int args_start = optind + 1;

        if (args_start < argc) {
            ctx.init_dir = argv[args_start];
        } else {
            ctx.init_dir = ".";
        }
    } else {
        std::cerr << "Unknown command: " << cmd << "\n";
        return CommandResult::ExitFailure;
    }

    return CommandResult::Run;
}

}
