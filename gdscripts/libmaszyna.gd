@tool
extends EditorPlugin

func _enter_tree():
    add_autoload_singleton("PlayerSystem", "res://addons/libmaszyna/player/player_system.gd")
    add_autoload_singleton("MultiPlayerManager", "res://addons/libmaszyna/player/multiplayer_manager.gd")
    add_autoload_singleton("Console", "res://addons/libmaszyna/utility/console.gd")
    add_custom_project_setting("maszyna/game/multiplayer/host", "127.0.0.1", TYPE_STRING)
    add_custom_project_setting("maszyna/game/multiplayer/port", 9797, TYPE_INT)


func _exit_tree():
    remove_autoload_singleton("Console")
    remove_autoload_singleton("MultiPlayerManager")
    remove_autoload_singleton("PlayerSystem")



func add_custom_project_setting(name: String, default_value, type: int, hint: int = PROPERTY_HINT_NONE, hint_string: String = "") -> void:

    if ProjectSettings.has_setting(name): return

    var setting_info: Dictionary = {
        "name": name,
        "type": type,
        "hint": hint,
        "hint_string": hint_string
    }

    ProjectSettings.set_setting(name, default_value)
    ProjectSettings.add_property_info(setting_info)
    ProjectSettings.set_initial_value(name, default_value)
