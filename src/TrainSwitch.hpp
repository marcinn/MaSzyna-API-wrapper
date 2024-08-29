#pragma once
#include <godot_cpp/classes/node.hpp>
#include "TrainPart.hpp"


namespace godot {
    class TrainSwitch : public TrainPart {
            GDCLASS(TrainSwitch, TrainPart)

        private:
            static void _bind_methods();
            bool pushed = false;

        public:
            void set_pushed(const bool p_state);
            bool get_pushed() const;

            TrainSwitch();
            ~TrainSwitch() override = default;
    };
} // namespace godot
