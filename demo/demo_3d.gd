extends Node3D

@onready var world = $WorldEnvironment

func _auto_user_settings_visibility():
    var game_dir = UserSettings.get_maszyna_game_dir()
    $UserSettingsPanel.visible = not game_dir or FileAccess.file_exists(game_dir)

func _update_render_settings():
    var viewport = get_tree().root.get_viewport()
    var world3d:World3D = viewport.world_3d
    world3d.environment.sdfgi_enabled = UserSettings.get_setting("render", "sdfgi_enabled", true)
    world3d.environment.volumetric_fog_enabled = UserSettings.get_setting("render", "volumetric_fog_enabled", true)
    world3d.environment.ssao_enabled = UserSettings.get_setting("render", "ssao_enabled", true)
    world3d.environment.ssil_enabled = UserSettings.get_setting("render", "ssil_enabled", true)
    world3d.environment.ssr_enabled = UserSettings.get_setting("render", "ssr_enabled", true)
    var scale = UserSettings.get_setting("render", "scale", 100)
    if scale < 100:
        viewport.scaling_3d_mode = Viewport.SCALING_3D_MODE_BILINEAR
        viewport.scaling_3d_scale = scale * 0.01
    else:
        viewport.scaling_3d_mode = Viewport.SCALING_3D_MODE_BILINEAR
        viewport.scaling_3d_scale = 1.0

    DisplayServer.window_set_vsync_mode(
        DisplayServer.VSYNC_ENABLED
        if UserSettings.get_setting("window", "vsync_enabled", true)
        else DisplayServer.VSYNC_DISABLED
    )
    viewport.screen_space_aa = (
        viewport.SCREEN_SPACE_AA_FXAA
        if UserSettings.get_setting("render", "fxaa_enabled", true)
        else viewport.SCREEN_SPACE_AA_DISABLED
    )

func _android_ready_pck():
    OS.request_permissions()
    for x in DirAccess.get_directories_at("/sdcard/"):
        LogSystem.info(x)

    # TODO: packs should be installed via mod-browser, not hardcoded
    var pck_path = "/sdcard/maszyna/maszyna-base.pck"
    if FileAccess.file_exists(pck_path):
        LogSystem.info("MaSzyna base pack exists. Loading %s" % pck_path)
        if ProjectSettings.load_resource_pack(pck_path):
            LogSystem.info("MaSzyna base pack loaded.")
            # Force set game dir to base PCK path
            UserSettings.save_maszyna_game_dir("res://mods/maszyna-base")
        else:
            LogSystem.error("Can't load MaSzyna base pack")
    else:
        LogSystem.error("MaSzyna base pack does not exist!")

func _android_ready_original_files():
    OS.request_permissions()
    UserSettings.save_maszyna_game_dir("/sdcard/maszyna")

func _ready():
    if OS.has_feature("android"):
        _android_ready_original_files()

    _auto_user_settings_visibility()
    UserSettings.game_dir_changed.connect(_auto_user_settings_visibility)
    UserSettings.config_changed.connect(_update_render_settings)

    _update_render_settings()
    SceneryResourceLoader.enabled = false
    SceneryResourceLoader.loading_request.connect(_on_loading_started)
    SceneryResourceLoader.scenery_loaded.connect(_on_loading_finished)

func _on_loading_started():
    $LoadingLabel.visible = true
    $VirtualJoystick_Movement.visible = false
    $VirtualJoystick_LookRotate.visible = false
    $TopMenu.visible = false
    await get_tree().process_frame
    await get_tree().process_frame

func _on_loading_finished():
    $LoadingLabel.visible = false
    if OS.has_feature("mobile"):
        $VirtualJoystick_Movement.visible = true
        $VirtualJoystick_LookRotate.visible = true
        $TopMenu.visible = true

func _input(event):
    if event.is_action_pressed("user_settnigs_toggle"):
        $UserSettingsPanel.visible = not $UserSettingsPanel.visible

    if event.is_action_pressed("hud_toggle"):
        $DebugHUD.visible = not $DebugHUD.visible

func _on_user_settings_panel_visibility_changed():
    var game_dir = UserSettings.get_maszyna_game_dir()
    $UserSettingsPanel/VBoxContainer/GameDirNotSet.visible = not game_dir or FileAccess.file_exists(game_dir)


func _on_loading_screen_fadein_finished() -> void:
    SceneryResourceLoader.enabled = true


func _on_enter_train_btn_pressed() -> void:
    var ev = InputEventAction.new()
    ev.action = "change_vehicle"
    ev.pressed = true
    Input.parse_input_event(ev)

func _on_toggle_cabin_btn_pressed() -> void:
    var ev = InputEventAction.new()
    ev.action = "cabin_mode_toggle"
    ev.pressed = true
    Input.parse_input_event(ev)


func _on_settings_btn_pressed() -> void:
    var ev = InputEventAction.new()
    ev.action = "user_settnigs_toggle"
    ev.pressed = true
    Input.parse_input_event(ev)


func _on_forward_btn_button_down() -> void:
    $Player.set_movement(-Vector3.FORWARD)


func _on_forward_btn_button_up() -> void:
    $Player.set_movement(Vector3.ZERO)


func _on_backward_btn_button_down() -> void:
    $Player.set_movement(Vector3.FORWARD)


func _on_backward_btn_button_up() -> void:
    $Player.set_movement(Vector3.ZERO)


func _on_controls_pressed() -> void:
    var ev = InputEventAction.new()
    ev.action = "hud_toggle"
    ev.pressed = true
    Input.parse_input_event(ev)
