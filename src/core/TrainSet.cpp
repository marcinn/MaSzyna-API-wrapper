#include <godot_cpp/variant/utility_functions.hpp>
#include "RailVehicle.hpp"
#include "TrainSet.hpp"

namespace godot {

    void TrainSet::_bind_methods() {
        ClassDB::bind_method(D_METHOD("_init", "_start_car"), &TrainSet::_init);
        ClassDB::bind_method(D_METHOD("get_by_index", "index"), &TrainSet::get_by_index);
        ClassDB::bind_method(D_METHOD("to_array"), &TrainSet::to_array);
        ClassDB::bind_method(D_METHOD("get_head"), &TrainSet::get_head);
        ClassDB::bind_method(D_METHOD("get_tail"), &TrainSet::get_tail);
    }

    TrainSet::TrainSet() {}

    void TrainSet::_init(Ref<RailVehicle> _start_car) {
        start_vehicle = _start_car;
    }

    Ref<RailVehicle> TrainSet::get_by_index(int index) {
        Ref<RailVehicle> current;
        if (index >= 0) {
            current = get_head();
            for (int i = 0; i < index && current.is_valid(); ++i) {
                current = current->back;
            }
        } else {
            current = get_tail();
            for (int i = -1; i > index && current.is_valid(); --i) {
                current = current->front;
            }
        }
        if (!current.is_valid()) {
            UtilityFunctions::push_error("Index out of range.");
        }
        return current;
    }

    Array TrainSet::to_array() const {
        Array result;
        Ref<RailVehicle> current = get_head();
        while (current.is_valid()) {
            result.append(current);
            current = current->back;
        }
        return result;
    }

    Ref<RailVehicle> TrainSet::get_head() const {
        Ref<RailVehicle> current = start_vehicle;
        while (current->front.is_valid()) {
            current = current->front;
        }
        return current;
    }

    Ref<RailVehicle> TrainSet::get_tail() const {
        Ref<RailVehicle> current = start_vehicle;
        while (current->back.is_valid()) {
            current = current->back;
        }
        return current;
    }
} // namespace godot
