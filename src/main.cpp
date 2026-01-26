#include "core/core.h"
#include "cli/command_parser.h"

int main(int argc, char *argv[]) {
    switch (cli::parse_command(argc, argv)) {
        case cli::CommandResult::Run:
            core::run();
            return 0;
        case cli::CommandResult::ExitSuccess:
            return 0;
        case cli::CommandResult::ExitFailure:
            return 1;
    }
}
