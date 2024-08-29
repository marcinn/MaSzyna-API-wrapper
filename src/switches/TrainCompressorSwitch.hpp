#pragma once
#include <godot_cpp/classes/node.hpp>
#include "../TrainSwitch.hpp"


namespace godot {
    class TrainCompressorSwitch : public TrainSwitch {
            GDCLASS(TrainCompressorSwitch, TrainSwitch)

        private:
            static void _bind_methods();

        protected:
            virtual void _do_update_internal_mover(TMoverParameters *mover) override;
            virtual void _do_fetch_state_from_mover(TMoverParameters *mover, Dictionary &state) override;

        public:
            TrainCompressorSwitch();
            ~TrainCompressorSwitch() override = default;
    };
} // namespace godot
