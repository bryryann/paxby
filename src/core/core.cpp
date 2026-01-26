#include "core/core.h"

#include <iostream>

namespace core {

void run(const Context &ctx) {
    if (ctx.verbose) {
        std::cout << "Verbose mode enabled\n";
    }

    std::cout << "Running...\n";
}

}
