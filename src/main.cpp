// main.cpp
//
// Application entrypoint.

#include "core/core.h"
#include "core/context.h"
#include "cli/command_parser.h"

int main(int argc, char *argv[]) {
    core::Context ctx;

    switch (cli::parse_command(argc, argv, ctx)) {
        case cli::CommandResult::Run:
            core::run(ctx);
            return 0;
        case cli::CommandResult::ExitSuccess:
            return 0;
        case cli::CommandResult::ExitFailure:
            return 1;
    }
}
