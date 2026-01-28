#include "core/core.h"
#include "core/commands.h"

#include <iostream>

namespace core {

void run(const Context &ctx) {
    if (ctx.verbose) {
        std::cout << "Verbose mode enabled\n";
    }

    switch (ctx.command) {
        case Command::Init:
            commands::run_init(ctx);

            break;

        case Command::None:
            std::cout << "none\n";

            break;
    }
}

}
