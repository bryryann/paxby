#pragma once

namespace core {

enum class Command {
    None,
    Init,
};

struct Context {
    bool show_help = false;
    bool verbose = false;

    Command command = Command::None;
};

}
