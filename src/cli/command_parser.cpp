// command_parser.cpp
//
// Parse commands, subcommands, options and arguments.
// Create context object and decide whether to run or exit application.

#include "cli/cli.h"
#include "cli/command_parser.h"
#include "utils/string.h"

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
    while ((opt = getopt_long(argc, argv, "+hv", options, nullptr)) != -1) {
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

    std::string cmd = argv[optind++];

    // --- init ---
    if (cmd == "init") {
        ctx.command = core::Command::Init;

        if (optind < argc) {
            ctx.init_dir = argv[optind];
        } else {
            ctx.init_dir = ".";
        }
    }
    // --- add ---
    else if (cmd == "add") {
        ctx.command = core::Command::Add;

        if (optind >= argc) {
            std::cerr << "No content provided for add\n";
            return CommandResult::ExitFailure;
        }

        ctx.title = argv[optind++];

        int add_opt;
        while ((add_opt = getopt_long(argc, argv, "t:p:d:", add_options, nullptr)) != -1) {
            switch (add_opt) {
                case 't':
                    utils::add_comma_separated(ctx.tags, optarg);
                    break;

                case 'p':
                    ctx.priority = optarg;
                    break;

                case 'd':
                    ctx.due_date = optarg;
                    break;

                default:
                    return CommandResult::ExitFailure;
            }
        }
    }
    // --- unknown command ---
    else {
        std::cerr << "Unknown command: " << cmd << "\n";
        return CommandResult::ExitFailure;
    }

    return CommandResult::Run;
}

}
