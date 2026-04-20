// main.cpp
//
// Application entrypoint.

#include "core/context.h"
#include "cli/cli.h"
#include "cli/command_parser.h"
#include "storage/json_task_repository.h"
#include "storage/bin_task_repository.h"
#include "config/config_json.h"

int main(int argc, char *argv[]) {
    core::Context ctx;

    std::filesystem::path app_dir = ".paxby";
    std::filesystem::path config_dir = app_dir / "config.json";

    storage::JsonTaskRepository json_repo(app_dir);
    storage::BinTaskRepository  bin_repo(app_dir);

    auto cmd = cli::parse_command(argc, argv, ctx);
    switch (cmd) {
        case cli::CommandResult::Run: {
            auto cfg = config::load_config(config_dir);

            switch (cfg.storage_file_type) {
                case core::FileType::Binary:
                    cli::run(ctx, bin_repo);
                    break;

                case core::FileType::Json:
                    cli::run(ctx, json_repo);
                    break;
            }
            return 0;
        }

        case cli::CommandResult::ExitSuccess:
            return 0;

        case cli::CommandResult::ExitFailure:
            return 1;
    }
}
