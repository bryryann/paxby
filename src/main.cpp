// main.cpp
//
// Application entrypoint.

#include "core/context.h"
#include "cli/cli.h"
#include "cli/command_parser.h"
#include "storage/json_task_repository.h"

int main(int argc, char *argv[]) {
    core::Context ctx;

    std::filesystem::path app_dir = ".paxby";

    storage::JsonTaskRepository repo(app_dir);

    switch (cli::parse_command(argc, argv, ctx)) {
        case cli::CommandResult::Run:
            cli::run(ctx, repo);
            return 0;
        case cli::CommandResult::ExitSuccess:
            return 0;
        case cli::CommandResult::ExitFailure:
            return 1;
    }
}
