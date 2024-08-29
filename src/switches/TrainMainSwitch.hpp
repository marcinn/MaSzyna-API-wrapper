#pragma once
#include <godot_cpp/classes/node.hpp>
#include "../TrainSwitch.hpp"


namespace godot {
    class TrainMainSwitch : public TrainSwitch {
            GDCLASS(TrainMainSwitch, TrainSwitch)

        private:
            static void _bind_methods();

        protected:
            virtual void _do_update_internal_mover(TMoverParameters *mover) override;
            virtual void _do_fetch_state_from_mover(TMoverParameters *mover, Dictionary &state) override;

        public:
            TrainMainSwitch();
            ~TrainMainSwitch() override = default;
    };
} // namespace godot
