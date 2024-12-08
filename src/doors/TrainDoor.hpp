#pragma once
#include "../core/TrainPart.hpp"

namespace godot {
    class TrainController;
    class TrainDoor final : public TrainPart {
            GDCLASS(TrainDoor, TrainPart)

        protected:
            void _do_update_internal_mover(TMoverParameters *mover) override;
            void _do_fetch_state_from_mover(TMoverParameters *mover, Dictionary &state) override;
            void _do_process_mover(TMoverParameters *mover, double delta) override;
            void _register_commands() override;
            void _unregister_commands() override;

        public:
            enum DoorPermitLight {
                DOOR_PERMIT_LIGHT_CONTINUOUS,
                DOOR_PERMIT_LIGHT_FLASHING_ON_PERMISSION_WITH_STEP,
                DOOR_PERMIT_LIGHT_FLASHING_ON_PERMISSION,
                DOOR_PERMIT_LIGHT_FLASHING_ALWAYS
            };

            enum DoorSide { DOOR_SIDE_RIGHT, DOOR_SIDE_LEFT };
            enum DoorState { DOOR_STATE_CLOSE, DOOR_STATE_OPEN };
            enum DoorVoltage {
                DOOR_VOLTAGE_AUTO,
                DOOR_VOLTAGE_0,
                DOOR_VOLTAGE_12,
                DOOR_VOLTAGE_24,
                DOOR_VOLTAGE_112,
            };
            enum DoorType {
                DOOR_TYPE_SHIFT,
                DOOR_TYPE_ROTATE,
                DOOR_TYPE_FOLD,
                DOOR_TYPE_PLUG,
            };
            enum DoorPlatformType { DOOR_PLATFORM_TYPE_SHIFT, DOOR_PLATFORM_TYPE_ROTATE };

            enum DoorControls {
                DOOR_CONTROLS_PASSENGER,
                DOOR_CONTROLS_AUTOMATIC,
                DOOR_CONTROLS_DRIVER,
                DOOR_CONTROLS_CONDUCTOR,
                DOOR_CONTROLS_MIXED,
            };

            TrainDoor();
            ~TrainDoor() override = default;

            static void _bind_methods();
            void set_door_type(DoorType p_door_type);
            DoorType get_door_type() const;
            void set_door_open_time(float p_value);
            float get_door_open_time() const;
            void set_open_speed(float p_value);
            float get_open_speed() const;
            void set_close_speed(float p_value);
            float get_close_speed() const;
            void set_door_max_shift(float p_max_shift);
            float get_door_max_shift() const;
            void set_door_open_method(DoorControls p_open_method);
            DoorControls get_door_open_method() const;
            void set_door_close_method(DoorControls p_close_method);
            DoorControls get_door_close_method() const;
            void set_door_voltage(DoorVoltage p_voltage);
            DoorVoltage get_door_voltage() const;
            void set_door_close_warning(bool p_close_warning);
            bool get_door_close_warning() const;
            void set_auto_door_close_warning(bool p_auto_close_warning);
            bool get_auto_door_close_warning() const;
            void set_door_open_delay(float p_open_delay);
            float get_door_open_delay() const;
            void set_door_close_delay(float p_close_delay);
            float get_door_close_delay() const;
            void set_door_open_with_permit(float p_holding_time);
            float get_door_open_with_permit() const;
            void set_has_lock(bool p_blocked);
            bool get_has_lock() const;
            void set_door_max_shift_plug(float p_max_shift_plug);
            float get_door_max_shift_plug() const;
            void set_door_permit_list(const Array &p_permit_list);
            Array get_door_permit_list() const;
            void set_door_permit_list_default(int p_permit_list_default);
            int get_door_permit_list_default() const;
            void set_door_auto_close_remote(bool p_auto_close);
            bool get_door_auto_close_remote() const;
            void set_door_auto_close_velocity(float p_vel);
            float get_door_auto_close_velocity() const;
            void set_door_platform_max_speed(double p_max_speed);
            double get_door_platform_max_speed() const;
            void set_door_platform_max_shift(float p_max_shift);
            float get_door_platform_max_shift() const;
            void set_door_platform_speed(float p_speed);
            float get_door_platform_speed() const;
            void set_platform_type(DoorPlatformType p_type);
            DoorPlatformType get_platform_type() const;
            void set_mirror_max_shift(double p_max_shift);
            double get_mirror_max_shift() const;
            void set_mirror_vel_close(double p_vel_close);
            double get_mirror_vel_close() const;
            void set_door_permit_required(bool p_permit_required);
            bool get_door_permit_required() const;
            void set_door_permit_light_blinking(DoorPermitLight p_blinking_mode);
            DoorPermitLight get_door_permit_light_blinking() const;

            void permit_door_step(const bool p_state);
            void permit_doors(const DoorSide p_side, const bool p_state);
            void permit_left_doors(const bool p_state);
            void permit_right_doors(const bool p_state);
            void operate_doors(const DoorSide p_side, const bool p_state);
            void operate_left_doors(const bool p_state);
            void operate_right_doors(const bool p_state);
            void set_lock_doors(const bool p_state);
            void set_doors_remote_only(const bool p_state);
            void next_door_permit_preset();
            void previous_door_permit_preset();

        private:
            // Maszyna Mover has no consts for voltages
            const std::map<DoorVoltage, int> voltageMap = {
                    {DOOR_VOLTAGE_0, 0}, {DOOR_VOLTAGE_12, 12}, {DOOR_VOLTAGE_24, 24}, {DOOR_VOLTAGE_112, 112}};

            // Maszyna Mover has no consts for door types
            const std::map<DoorType, int> doorTypeMap = {
                    {DOOR_TYPE_SHIFT, 1}, {DOOR_TYPE_ROTATE, 2}, {DOOR_TYPE_FOLD, 3}, {DOOR_TYPE_PLUG, 4}};
            //
            // Maszyna Mover has no consts for door platform types
            const std::map<DoorPlatformType, int> doorPlatformTypeMap = {
                    {DOOR_PLATFORM_TYPE_SHIFT, 1}, {DOOR_PLATFORM_TYPE_ROTATE, 2}};

            // Maszyna Mover has no consts for permit lights
            const std::map<DoorPermitLight, int> doorPermitLightMap = {
                    {DOOR_PERMIT_LIGHT_CONTINUOUS, 0},
                    {DOOR_PERMIT_LIGHT_FLASHING_ON_PERMISSION_WITH_STEP, 1},
                    {DOOR_PERMIT_LIGHT_FLASHING_ON_PERMISSION, 2},
                    {DOOR_PERMIT_LIGHT_FLASHING_ALWAYS, 3}};

            const std::unordered_map<DoorControls, Maszyna::control_t> doorControlsMap = {
                    {DoorControls::DOOR_CONTROLS_PASSENGER, Maszyna::control_t::passenger},
                    {DoorControls::DOOR_CONTROLS_AUTOMATIC, Maszyna::control_t::autonomous},
                    {DoorControls::DOOR_CONTROLS_DRIVER, Maszyna::control_t::driver},
                    {DoorControls::DOOR_CONTROLS_CONDUCTOR, Maszyna::control_t::conductor},
                    {DoorControls::DOOR_CONTROLS_MIXED, Maszyna::control_t::mixed},
            };

            /**
             * Type of the door. Default value from internal mover
             *
             */
            DoorType door_type = DoorType::DOOR_TYPE_ROTATE;
            /**
             * The type of door (opening method). Default value from internal mover
             */
            DoorControls door_open_method = DoorControls::DOOR_CONTROLS_PASSENGER;

            /**
             * The type of door (closing method). Default value from internal mover
             */
            DoorControls door_close_method = DoorControls::DOOR_CONTROLS_PASSENGER;

            /**
             * Time period for which door would stay opened. Default value from internal mover
             */
            float door_open_time = -1.0f;

            /**
             * Speed of opening the doors. Default value from internal mover
             */
            float open_speed = 1.0f;

            /**
             * Speed of closing the door. Default value from internal mover
             */
            float close_speed = 1.0f;

            /**
             * The width (or angle) of the door fully opening. Default value from internal mover
             */
            float door_max_shift = 0.0f;

            /**
             * Low voltage circuit voltage required for door control. Default value from internal mover
             */
            DoorVoltage door_voltage = DoorVoltage::DOOR_VOLTAGE_AUTO;

            /**
             * Buzzer before closing the door. Default value from internal mover
             */
            bool door_close_warning = false;

            /**
             * When you press the door closing button, a buzzer is activated, when you release it, the door closes.
             * Default value from internal mover
             */
            bool auto_door_close_warning = false;

            /**
             * Door closing delay, in seconds. Default value from internal mover
             */
            float door_close_delay = 0.0;

            /**
             * Door opening delay, in seconds. Default value from internal mover
             */
            float door_open_delay = 0.0;

            /**
             * Opening a train door by holding the impulse opening permission button, in seconds of holding the button
             */
            float door_open_with_permit = 0.0;

            /**
             * Is doors has lock.
             */
            bool has_lock = false;

            /**
             * The amount of rebound for Plug type doors (rebound-sliding), in meters. Default value from internal mover
             */
            float door_max_shift_plug = 0.0f;

            /**
             * Door programmer configuration. Number in the range of 0-3 where 0=no permissions, 1=allows left
             * door operation, 2=right door, 3=all
             */
            Array door_permit_list = Array({"0", "0", "0"});

            /**
             * The default knob position is from the set defined by the door_permit_list entry; positions are numbered
             * from 1. Default value from internal mover
             */
            int door_permit_list_default = -1;

            /**
             * Automatic closing of centrally opened doors after time has elapsed
             */
            bool door_auto_close_remote = false;

            /**
             * The speed at which the door automatically closes. Default value from internal mover
             */
            float door_auto_close_velocity = -1.0f;

            /**
             * Docs do not describe this properly. Need to figure this out
             */
            double platform_max_speed = 0.0;

            /**
             * Offset value in meters or rotation angle for a fully extended step. Default value from internal mover
             */
            float platform_max_shift = 0.0f;

            /**
             * The speed of the animation step, where 1.0 corresponds to an animation lasting one second, a value of 0.5
             * to two seconds, etc. Default value from internal mover
             */
            float platform_speed = 0.5f;

            /**
             * Rotation angle for fully extended mirror
             */
            double mirror_max_shift = 0.0;

            /**
             * The speed of the traction vehicle at which the external mirrors are automatically closed
             */
            double mirror_vel_close = 0.0;

            /**
             * Opening doors by passengers requires the train driver's consent. Default value from internal mover
             */
            bool door_permit_required = false;

            /**
             * Blinking permit light. Default value from internal mover
             */
            DoorPermitLight door_permit_light_blinking = DoorPermitLight::DOOR_PERMIT_LIGHT_CONTINUOUS;

            DoorPlatformType platform_type = DoorPlatformType::DOOR_PLATFORM_TYPE_ROTATE;

            /**
             * Describes the side where the doors are placed
             */
            DoorSide door_side = DoorSide::DOOR_SIDE_LEFT;
    };
} // namespace godot

VARIANT_ENUM_CAST(TrainDoor::DoorPermitLight)
VARIANT_ENUM_CAST(TrainDoor::DoorPlatformType)
VARIANT_ENUM_CAST(TrainDoor::DoorSide)
VARIANT_ENUM_CAST(TrainDoor::DoorState)
VARIANT_ENUM_CAST(TrainDoor::DoorControls)
VARIANT_ENUM_CAST(TrainDoor::DoorVoltage)
VARIANT_ENUM_CAST(TrainDoor::DoorType)
