#include "TrainEngine.hpp"

namespace godot {
    class TrainController;

    TrainEngine::TrainEngine() = default;

    void TrainEngine::_bind_methods() {
        ClassDB::bind_method(D_METHOD("set_main_switch_pressed"), &TrainEngine::set_main_switch_pressed);
        ClassDB::bind_method(D_METHOD("get_main_switch_pressed"), &TrainEngine::get_main_switch_pressed);
        ADD_PROPERTY(
                PropertyInfo(Variant::BOOL, "switches/main"), "set_main_switch_pressed", "get_main_switch_pressed");
    }

    void TrainEngine::_do_update_internal_mover(TMoverParameters *mover) {
        mover->EngineType = get_engine_type();

        /* FIXME: for testing purposes */
        mover->GroundRelay = true;
        mover->NoVoltRelay = true;
        mover->OvervoltageRelay = true;
        mover->DamageFlag = false;
        mover->EngDmgFlag = false;
        mover->ConvOvldFlag = false;
        /* end testing */
    }

    void TrainEngine::_do_process_mover(TMoverParameters *mover, const double delta) {
        mover->MainSwitch(main_switch_pressed);
    }

    void TrainEngine::_do_fetch_state_from_mover(TMoverParameters *mover, Dictionary &state) {
        state["engine_power"] = mover->EnginePower;
        state["engine_rpm"] = mover->nrot;
        state["engine_current"] = mover->Im;
    }

    void TrainEngine::set_main_switch_pressed(const bool p_state) {
        main_switch_pressed = p_state;
        _dirty = true;
    }

    bool TrainEngine::get_main_switch_pressed() const {
        return main_switch_pressed;
    }
} // namespace godot
