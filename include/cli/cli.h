// cli.h
//
// Settings and configurations used by the cli command parsing.
// Also define helper functions.

#pragma once

#include "core/context.h"
#include "storage/json_task_repository.h"

#include <getopt.h>

namespace cli {

extern struct option options[];

extern struct option add_options[];

void print_help();

void run(const core::Context &ctx, storage::JsonTaskRepository &repo);

}
