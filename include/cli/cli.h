// cli.h
//
// Settings and configurations used by the cli command parsing.
// Also define helper functions.

#pragma once

#include <getopt.h>

namespace cli {

extern struct option options[];

void print_help();

}
