#include <godot_cpp/variant/utility_functions.hpp>
#include "RailVehicle.hpp"
#include "TrainSet.hpp"

namespace godot {

    void RailVehicle::_bind_methods() {
        ClassDB::bind_method(D_METHOD("couple", "other_vehicle", "self_side", "other_side"), &RailVehicle::couple);
        ClassDB::bind_method(D_METHOD("couple_front", "other_vehicle", "other_side"), &RailVehicle::couple_front);
        ClassDB::bind_method(D_METHOD("couple_back", "other_vehicle", "other_side"), &RailVehicle::couple_back);
        ClassDB::bind_method(D_METHOD("uncouple_front"), &RailVehicle::uncouple_front);
        ClassDB::bind_method(D_METHOD("uncouple_back"), &RailVehicle::uncouple_back);
        ClassDB::bind_method(D_METHOD("get_trainset"), &RailVehicle::get_trainset);

        ADD_PROPERTY(
                PropertyInfo(Variant::OBJECT, "trainset", PROPERTY_HINT_RESOURCE_TYPE, "TrainSet"), "", "get_trainset");

        BIND_ENUM_CONSTANT(FRONT);
        BIND_ENUM_CONSTANT(BACK);
    }

    RailVehicle::RailVehicle() {
        trainset.instantiate();
        trainset->_init(this);
    }

    void RailVehicle::couple(Ref<RailVehicle> other_vehicle, Side self_side, Side other_side) {
        if (self_side == Side::FRONT && other_side == Side::BACK) {
            if (front.is_valid() || other_vehicle->back.is_valid()) {
                UtilityFunctions::push_error("One of the cars is already coupled.");
                return;
            }
            front = other_vehicle;
            other_vehicle->back = Ref(this);
        } else if (self_side == Side::BACK && other_side == Side::FRONT) {
            if (back.is_valid() || other_vehicle->front.is_valid()) {
                UtilityFunctions::push_error("One of the cars is already coupled.");
                return;
            }
            back = other_vehicle;
            other_vehicle->front = Ref(this);
        } else {
            UtilityFunctions::push_error("Invalid coupling sides specified.");
        }
    }

    void RailVehicle::couple_front(Ref<RailVehicle> other_vehicle, Side other_side) {
        couple(other_vehicle, Side::FRONT, other_side);
    }

    void RailVehicle::couple_back(Ref<RailVehicle> other_vehicle, Side other_side) {
        couple(other_vehicle, Side::BACK, other_side);
    }

    Ref<RailVehicle> RailVehicle::uncouple_front() {
        if (!front.is_valid()) {
            UtilityFunctions::push_error("No car coupled at the front.");
            return nullptr;
        }
        Ref<RailVehicle> uncoupled = front;
        front->back.unref();
        front.unref();
        return uncoupled;
    }

    Ref<TrainSet> RailVehicle::get_trainset() const {
        return trainset;
    }

    Ref<RailVehicle> RailVehicle::uncouple_back() {
        if (!back.is_valid()) {
            UtilityFunctions::push_error("No car coupled at the back.");
            return nullptr;
        }
        Ref<RailVehicle> uncoupled = back;
        back->front.unref();
        back.unref();
        return uncoupled;
    }
} // namespace godot
