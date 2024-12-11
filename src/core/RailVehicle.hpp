#ifndef RAILVEHICLE_HPP
#define RAILVEHICLE_HPP

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
    class TrainSet;

    class RailVehicle : public RefCounted {
            GDCLASS(RailVehicle, RefCounted);

        protected:
            static void _bind_methods();

        public:
            String id;
            Ref<RailVehicle> front;
            Ref<RailVehicle> back;
            Ref<TrainSet> trainset;

            enum Side {
                FRONT = 0,
                BACK,
            };

            RailVehicle();

            void couple(Ref<RailVehicle> other_vehicle, Side self_side, Side other_side);
            void couple_front(Ref<RailVehicle> other_vehicle, Side other_side);
            void couple_back(Ref<RailVehicle> other_vehicle, Side other_side);
            Ref<TrainSet> get_trainset() const;

            Ref<RailVehicle> uncouple_front();
            Ref<RailVehicle> uncouple_back();
    };
} // namespace godot

VARIANT_ENUM_CAST(RailVehicle::Side)

#endif // RAILVEHICLE_HPP
