@tool
extends EditorImportPlugin

func _get_recognized_extensions():
    return ["e3d"]

func _get_resource_type():
    return "PackedScene"

func _get_importer_name():
    return "libmaszyna.e3d"

func _get_import_order() -> int:
    return 10

func _get_import_options(preset, flags):
    return []

func _get_visible_name():
    return "MaSzyna E3D Importer"

func _get_save_extension():
    return "scn"

func _get_preset_count():
    return 0

func _get_priority():
    return 1

func _get_preset_name(i):
    return "default"


func _get_option_visibility(path: String, option_name: StringName, options: Dictionary) -> bool:
    return option_name != "mode"

func _propagate_owner(node, owner):
    for child in node.get_children():
        child.owner = owner
        _propagate_owner(child, owner)

func _import(source_file, save_path, options, platform_variants, gen_files):
    var file = FileAccess.open(source_file, FileAccess.READ)
    if file == null:
        push_error("Can't open file %s" % source_file)
        return FileAccess.get_open_error()

    print("Importing %s" % source_file)
    var scene = PackedScene.new()
    var e3dmodel = E3DParser.parse(file, options)
    print("Instantiating %s" % source_file)
    var node = E3DModelInstance.new()
    node.instancer = E3DModelInstance.Instancer.EDITABLE_NODES
    node.name = source_file.get_basename()
    node.data_path = source_file.get_base_dir()
    E3DNodesInstancer.instantiate(e3dmodel, node, true)
    print(node.get_children())
    print("Propagate owner")
    _propagate_owner(node, node)
    var output_path = "%s.%s" % [save_path, _get_save_extension()]
    print("Packing %s to %s" % [source_file, output_path])
    scene.pack(node)
    print("Saving %s to %s" % [source_file, output_path])
    var res = ResourceSaver.save(scene, output_path)
    print("Saved.")
    return res
