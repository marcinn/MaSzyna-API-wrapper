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
            bool converter_switch_pressed = false;
            bool compressor_switch_pressed = false;

        protected:
            void _do_update_internal_mover(TMoverParameters *mover) override;
            void _do_fetch_state_from_mover(TMoverParameters *mover, Dictionary &state) override;

        public:
            void set_converter_switch_pressed(const bool p_state);
            bool get_converter_switch_pressed() const;
            void set_compressor_switch_pressed(const bool p_state);
            bool get_compressor_switch_pressed() const;

            TrainElectricEngine();
            ~TrainElectricEngine() override = default;
    };
} // namespace godot
