// main.cpp
//
// Application entrypoint.

#include "core/context.h"
#include "cli/cli.h"
#include "cli/command_parser.h"

int main(int argc, char *argv[]) {
    core::Context ctx;

    switch (cli::parse_command(argc, argv, ctx)) {
        case cli::CommandResult::Run:
            cli::run(ctx);
            return 0;
        case cli::CommandResult::ExitSuccess:
            return 0;
        case cli::CommandResult::ExitFailure:
            return 1;
    }
}
