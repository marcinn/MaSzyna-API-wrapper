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

    void TrainSet::_init(RailVehicle *_start_car) {
        start_vehicle = _start_car;
    }

    RailVehicle *TrainSet::get_by_index(int index) {
        RailVehicle *current;
        if (index >= 0) {
            current = get_head();
            for (int i = 0; i < index && current != nullptr; ++i) {
                current = current->back;
            }
        } else {
            current = get_tail();
            for (int i = -1; i > index && current != nullptr; --i) {
                current = current->front;
            }
        }
        if (current == nullptr) {
            UtilityFunctions::push_error("Index out of range.");
        }
        return current;
    }

    Array TrainSet::to_array() const {
        Array result;
        RailVehicle *current = get_head();
        while (current != nullptr) {
            result.append(current);
            current = current->back;
        }
        return result;
    }

    RailVehicle *TrainSet::get_head() const {
        RailVehicle *current = start_vehicle;
        while (current->front != nullptr) {
            current = current->front;
        }
        return current;
    }

    RailVehicle *TrainSet::get_tail() const {
        RailVehicle *current = start_vehicle;
        while (current->back != nullptr) {
            current = current->back;
        }
        return current;
    }
} // namespace godot
