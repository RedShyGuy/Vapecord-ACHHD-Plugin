#include <CTRPluginFramework.hpp>
#include "core/RuntimeContext.hpp"

namespace CTRPluginFramework {
    RuntimeContext* RuntimeContext::instance = nullptr;

    RuntimeContext* RuntimeContext::getInstance() {
        if (instance == nullptr) {
            instance = new RuntimeContext();
        }
        return instance;
    }
}