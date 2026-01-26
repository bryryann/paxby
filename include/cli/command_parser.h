#pragma once

namespace cli {

enum class CommandResult {
    Run,
    ExitSuccess,
    ExitFailure
};

CommandResult parse_command(int argc, char **argv);

}
