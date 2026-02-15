// commands.h
//
// Implement the main commands and subcommands functions.

#pragma once

#include "core/context.h"
#include "storage/json_task_repository.h"

namespace commands {

void run_init(const core::Context &ctx);

void run_add(const core::Context &ctx, storage::JsonTaskRepository& repo);

void run_list(const core::Context &ctx, storage::JsonTaskRepository& repo);

}
