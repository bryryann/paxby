#include "io/exporter.h"
#include "core/tasks_json.h"

#include <nlohmann/json.hpp>
#include <memory>

// WARN: UNUSED. Feature not yet implemented.
namespace io {

class JsonExporter : public Exporter {
public:
    void export_tasks(
        const std::vector<core::Task>& tasks,
        std::ostream& out
    ) {
        nlohmann::json j = tasks;
        out << j.dump(4) << '\n';
    }
};

// exporter factory
std::unique_ptr<Exporter> make_exporter(core::ExportFormat fmt) {
    switch (fmt) {
        case core::ExportFormat::JSON:
            return std::make_unique<JsonExporter>();
        default:
            throw std::runtime_error("Unsupported export format.");
    }
}

}
