#include <godot_cpp/classes/gd_extension.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "TrainEngine.hpp"
#include "maszyna/McZapkie/MOVER.h"

namespace godot {
    class TrainController;

    TrainEngine::TrainEngine() {}

    void TrainEngine::_do_update_internal_mover(TMoverParameters *mover) {
        mover->EngineType = get_engine_type();
    }

    void TrainEngine::_do_fetch_state_from_mover(TMoverParameters *mover, Dictionary &state) {
        state["engine_power"] = mover->EnginePower;
        state["engine_rpm"] = mover->nrot;
        state["engine_current"] = mover->Im;
    }

    void TrainEngine::_bind_methods() {}

} // namespace godot
