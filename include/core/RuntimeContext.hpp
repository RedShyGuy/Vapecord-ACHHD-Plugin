#pragma once

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {
    class RuntimeContext {
        private:
            //add any global state variables here, with default values if needed

            RuntimeContext() = default;
            static RuntimeContext* instance;
        public:
            static RuntimeContext* getInstance();

            //add any getters/setters for the state variables here
    };
}