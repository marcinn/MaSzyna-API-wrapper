@tool
extends ResourceFormatLoader
class_name MaszynaMaterialResourceFormatLoader

var parser = load("res://addons/libmaszyna/materials/material_parser.gd").new()

func _get_recognized_extensions():
    return ["mat"]

func _handles_type(type):
    return type == "MaszynaMaterial"

func _get_resource_type(path: String):
    return "MaszynaMaterial"

func _load(path: String, original_path: String = "", use_sub_threads: bool = false, cache_mode: int = 0) -> Resource:
    return parser.parse(path)
