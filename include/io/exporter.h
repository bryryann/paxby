#pragma once

#include "core/context.h"
#include "core/tasks.h"

#include <memory>
#include <ostream>
#include <vector>

namespace io {

class Exporter {
public:
  virtual ~Exporter() = default;
  virtual void export_tasks(const std::vector<core::Task> &tasks,
                            std::ostream &out) = 0;
};

std::unique_ptr<Exporter> make_exporter(core::ExportFormat fmt);

} // namespace io
