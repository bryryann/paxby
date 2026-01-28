#include "core/core.h"

#include <iostream>

namespace core {

void run(const Context &ctx) {
    if (ctx.verbose) {
        std::cout << "Verbose mode enabled\n";
    }

    switch (ctx.command) {
        case Command::Init:
            std::cout << "init on: " << ctx.init_dir << "\n";
            break;
        case Command::None:
            std::cout << "none\n";
            break;
    }
}

}
