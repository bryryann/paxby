// command_parser.h
//
// Parse commands, subcommands, options and arguments.
// Create context object and decide whether to run or exit application.

#pragma once

#include "core/context.h"

namespace cli {

// Represents action to take after parsing commands.
enum class CommandResult {
    Run,
    ExitSuccess,
    ExitFailure
};

CommandResult parse_command(int argc, char **argv, core::Context &ctx);

}
