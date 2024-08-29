#pragma once
#include <godot_cpp/classes/node.hpp>
#include "TrainEngine.hpp"
#include "maszyna/McZapkie/MOVER.h"


namespace godot {
    class TrainController;

    class TrainElectricEngine : public TrainEngine {
            GDCLASS(TrainElectricEngine, TrainEngine)

        private:
            static void _bind_methods();

        public:
            TrainElectricEngine();
            ~TrainElectricEngine() override = default;
    };
} // namespace godot
