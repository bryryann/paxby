#pragma once

#include "core/context.h"

namespace cli {

enum class CommandResult {
    Run,
    ExitSuccess,
    ExitFailure
};

CommandResult parse_command(int argc, char **argv, core::Context &ctx);

}
