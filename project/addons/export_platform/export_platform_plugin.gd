@tool
extends EditorPlugin

var platform

func _enter_tree() -> void:
	# Initialization of the plugin goes here.
	platform = EditorExportPlatformTemplate.new()
	add_export_platform(platform)


func _exit_tree() -> void:
	# Clean-up of the plugin goes here.
	remove_export_platform(platform)
