# paxby

Directory-scoped C++ CLI application for tracking and managing project-specific tasks and to-dos.

## Installation

### Requirements

- CMake >= 3.20.
- C++20 compatible compiler.
- `nlohmann_json` installed in your system.

### Build

Clone the repository and build the project.
```
git clone https://github.com/bryryann/paxby.git
cd paxby

cmake -B build
cmake --build build
```

### Install (system-wide)
To install globally (e.g., `/usr/local/bin`):

```
sudo cmake --install build
```

You can now run:
```
paxby
```

### Install (local user)
To install without sudo:

```
cmake -B build -DCMAKE_INSTALL_PREFIX=$HOME/.local 
cmake --build build
cmake --install build
```

Make sure `~/.local/bin` is in your `PATH`.

```
export PATH="$HOME/.local/bin:$PATH"
```

## Usage

All paxby commands follow the pattern:
```
paxby [command] [options]
```

### Commands
- `init [directory]` - Initialize paxby in the given directory.
- `add "[task_description]" --tag [comma-separated_tags] --priority [low,medium,high] --due-date [YYYY-MM-DD]` - Add a new task to project.
- `list --page [page_number] --size [page_size]` - List all registered tasks.
- `show [task_id]` - Print task details.
- `done [task_id]` - Mark task as done.
- `delete [task_id]` - Delete task from registry.
- `export [file_type]` - Export tasks to different file format. (W.I.P.)

## Project structure

```
include/
src/
  cli/
  commands/
  config/
  core/
  io/
  storage/
  utils/
  main.cpp
```

---

# paxby

![C++](https://img.shields.io/badge/C%2B%2B-20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-%3E%3D3.20-brightgreen.svg)
![CLI](https://img.shields.io/badge/CLI-tool-lightgrey.svg)
![Status](https://img.shields.io/badge/status-active-success.svg)
![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
