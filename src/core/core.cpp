#include "core/core.h"

#include <iostream>

namespace core {

void run(const Context &ctx) {
    if (ctx.verbose) {
        std::cout << "Verbose mode enabled\n";
    }

    switch (ctx.command) {
        case Command::Init:
            std::cout << "init";
            break;
        case Command::None:
            std::cout << "none";
            break;
    }
}

}
