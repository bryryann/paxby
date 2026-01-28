// core.h
//
// Define business-logic related code application dependencies.
// Independent from any other library.

#pragma once

#include "core/context.h"

#include <getopt.h>

namespace core {

void run(const Context &ctx);

}
