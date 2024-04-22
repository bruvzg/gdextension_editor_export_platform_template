#include "editor_export_platform_template.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

/**************************************************************************/
/* Base                                                                   */
/**************************************************************************/

EditorExportPlatformTemplate::EditorExportPlatformTemplate() {
	// Load icons.
    String svg = R"("<svg xmlns="http://www.w3.org/2000/svg" width="32" height="32"><path d="M12.443 21.64q-.196-2.044.197-3.459.393-1.454 1.06-2.476.708-1.061 1.573-1.808.904-.786 1.65-1.493.787-.708 1.298-1.454.51-.787.51-1.848 0-1.375-.785-2.2-.747-.826-2.712-.826-.63 0-1.337.157-.707.118-1.415.393-.707.236-1.375.59-.63.314-1.14.668L8.002 4.11q1.493-1.022 3.42-1.69 1.964-.668 4.716-.668 3.694 0 5.777 1.808 2.083 1.768 2.083 4.795 0 2.004-.55 3.34-.511 1.297-1.297 2.24-.786.905-1.73 1.612-.943.707-1.729 1.533-.786.786-1.336 1.847t-.55 2.712zm-.786 5.581q0-1.376.865-2.162.864-.825 2.28-.825 1.493 0 2.357.825.865.786.865 2.162t-.865 2.201-2.358.825q-1.415 0-2.28-.825t-.864-2.201" aria-label="?" style="font-weight:700;font-size:16px;line-height:1.25;font-family:&quot;PT Sans&quot;;-inkscape-font-specification:&quot;PT Sans Bold&quot;;fill:#00f;stroke-width:2.45644"/></svg>")";
    Ref<Image> img;
    img.instantiate();
    img->load_svg_from_buffer(svg.to_ascii_buffer(), EditorInterface::get_singleton()->get_editor_scale());
    logo = ImageTexture::create_from_image(img);

    Ref<Theme> theme = EditorInterface::get_singleton()->get_editor_theme();
    if (theme.is_valid()) {
        run_icon = theme->get_icon("Play", "EditorIcons");
        stop_icon = theme->get_icon("Stop", "EditorIcons");
    }

	// TODO: If One-click deploy device/simulator detection is supported, start thread to monitor and enum devices.
}

String EditorExportPlatformTemplate::_get_os_name() const {
    return "DOS";
}

String EditorExportPlatformTemplate::_get_name() const {
    return "MS-DOS";
}

Ref<Texture2D> EditorExportPlatformTemplate::_get_logo() const {
    return logo;
}

void EditorExportPlatformTemplate::_bind_methods() {
	// Register callback for the custom file format saving, only if fully customized export is used.
    ClassDB::bind_method(D_METHOD("_save_file", "path", "data", "file_no", "total", "enc_in", "enc_ex", "key", "save_path"), &EditorExportPlatformTemplate::_save_file);
    ClassDB::bind_method(D_METHOD("_save_so", "path", "tags", "target_folder", "save_path"), &EditorExportPlatformTemplate::_save_so);
}

PackedStringArray EditorExportPlatformTemplate::_get_binary_extensions(const Ref<EditorExportPreset> &preset) const {
	// Array or supported extensions shown in the export file save dialog, this includes archive extensions (e.g, DMG and ZIP on macOS) if supported.
    PackedStringArray ret;
    ret.push_back("com");
    return ret;
}

bool EditorExportPlatformTemplate::_is_executable(const String &path) const {
	// Used to set Unix +x premission, skip.
    return false;
}

/**************************************************************************/
/* Export Options and Featues                                             */
/**************************************************************************/

TypedArray<Dictionary> EditorExportPlatformTemplate::_get_export_options() const {
    TypedArray<Dictionary> options;
    {
        Dictionary opt;
        opt["name"] = "custom_template/debug";
        opt["type"] = Variant::STRING;
        opt["hint"] = PROPERTY_HINT_GLOBAL_FILE;
        opt["hint_string"] = "*.com";
        opt["default_value"] = String();
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "custom_template/release";
        opt["type"] = Variant::STRING;
        opt["hint"] = PROPERTY_HINT_GLOBAL_FILE;
        opt["hint_string"] = "*.com";
        opt["default_value"] = String();
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "debug/export_console_wrapper";
        opt["type"] = Variant::INT;
        opt["hint"] = PROPERTY_HINT_ENUM;
        opt["hint_string"] = "No,Debug Only,Debug and Release";
        opt["default_value"] = 1;
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "binary_format/embed_pck";
        opt["type"] = Variant::BOOL;
        opt["default_value"] = false;
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "texture_format/s3tc_bptc";
        opt["type"] = Variant::BOOL;
        opt["default_value"] = true;
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "texture_format/etc2_astc";
        opt["type"] = Variant::BOOL;
        opt["default_value"] = false;
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "archive/use_custom_format";
        opt["type"] = Variant::BOOL;
        opt["default_value"] = false;
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "options/show_hidden";
        opt["type"] = Variant::BOOL;
        opt["default_value"] = false;
        opt["update_visibility"] = true;
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "options/hidden";
        opt["type"] = Variant::STRING;
        opt["default_value"] = String();
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "options/must_be_moo";
        opt["type"] = Variant::STRING;
        opt["default_value"] = "MOO!";
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "binary_format/architecture";
        opt["type"] = Variant::STRING;
        opt["hint"] = PROPERTY_HINT_ENUM;
        opt["hint_string"] = "x86_16,x86_32";
        opt["default_value"] = "86_16";
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "ssh_remote_deploy/enabled";
        opt["type"] = Variant::BOOL;
        opt["default_value"] = false;
        opt["update_visibility"] = true;
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "ssh_remote_deploy/host";
        opt["type"] = Variant::STRING;
        opt["default_value"] = "user@host_ip";
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "ssh_remote_deploy/port";
        opt["type"] = Variant::STRING;
        opt["default_value"] = "22";
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "ssh_remote_deploy/extra_args_ssh";
        opt["type"] = Variant::STRING;
        opt["hint"] = PROPERTY_HINT_MULTILINE_TEXT;
        opt["default_value"] = "";
        options.push_back(opt);
    }
    {
        Dictionary opt;
        opt["name"] = "ssh_remote_deploy/extra_args_scp";
        opt["type"] = Variant::STRING;
        opt["hint"] = PROPERTY_HINT_MULTILINE_TEXT;
        opt["default_value"] = "";
        options.push_back(opt);
    }
    {
        String run_script = "#!/usr/bin/env bash\n"
                    "export DISPLAY=:0\n"
                    "unzip -o -q \"{temp_dir}/{archive_name}\" -d \"{temp_dir}\"\n"
                    "\"{temp_dir}/{exe_name}\" {cmd_args}";

        Dictionary opt;
        opt["name"] = "ssh_remote_deploy/run_script";
        opt["type"] = Variant::STRING;
        opt["hint"] = PROPERTY_HINT_MULTILINE_TEXT;
        opt["default_value"] = run_script;
        options.push_back(opt);
    }
    {
        String cleanup_script = "#!/usr/bin/env bash\n"
                        "kill $(pgrep -x -f \"{temp_dir}/{exe_name} {cmd_args}\")\n"
                        "rm -rf \"{temp_dir}\"";
        Dictionary opt;
        opt["name"] = "ssh_remote_deploy/cleanup_script";
        opt["type"] = Variant::STRING;
        opt["hint"] = PROPERTY_HINT_MULTILINE_TEXT;
        opt["default_value"] = cleanup_script;
        options.push_back(opt);
    }

    return options;
}

bool EditorExportPlatformTemplate::_should_update_export_options() {
    return false;
}

bool EditorExportPlatformTemplate::_get_export_option_visibility(const Ref<EditorExportPreset> &preset, const String &option) const {
    if (preset.is_null()) {
		return true;
	}

	bool advanced_options_enabled = preset->are_advanced_options_enabled();

	// Hide SSH options.
	bool ssh = preset->get("ssh_remote_deploy/enabled");
	if (!ssh && option != "ssh_remote_deploy/enabled" && option.begins_with("ssh_remote_deploy/")) {
		return false;
	}
	if (option == "dotnet/embed_build_outputs") {
		return advanced_options_enabled;
	}

    if (option != "options/hidden") {
        return true;
    } else {
        return preset->get("options/show_hidden").operator bool();
    }
}

String EditorExportPlatformTemplate::_get_export_option_warning(const Ref<EditorExportPreset> &preset, const StringName &option) const {
    if (preset.is_null()) {
        return String();
    }

    String warning;
    if (preset->get("options/must_be_moo") != "MOO!") {
        warning = "Not \"MOO!\"";
    }
    return warning;
}

PackedStringArray EditorExportPlatformTemplate::_get_platform_features() const {
	// Returns features always set for the platform.
    PackedStringArray ret;
    ret.push_back("pc");
    ret.push_back("ms_dos");
    return ret;
}

PackedStringArray EditorExportPlatformTemplate::_get_preset_features(const Ref<EditorExportPreset> &preset) const {
	// Returns features based on the current preset.
    PackedStringArray features;
    if (preset->get("texture_format/s3tc_bptc")) {
		features.push_back("s3tc");
		features.push_back("bptc");
	}
	if (preset->get("texture_format/etc2_astc")) {
		features.push_back("etc2");
		features.push_back("astc");
	}
	features.push_back(preset->get("binary_format/architecture"));

    return features;
}

/**************************************************************************/
/* Configration Validation                                                */
/**************************************************************************/

bool EditorExportPlatformTemplate::_can_export(const Ref<EditorExportPreset> &preset, bool debug) const {
    bool valid = true;
    valid = valid && _has_valid_export_configuration(preset, debug);
    valid = valid && _has_valid_project_configuration(preset);
    return valid;
}

bool EditorExportPlatformTemplate::_has_valid_export_configuration(const Ref<EditorExportPreset> &preset, bool debug) const {
    String err;
	bool valid = false;

	// Look for export templates (first official, and if defined custom templates).
	String arch = preset->get("binary_format/architecture");
	Dictionary dinfo = find_export_template(get_template_file_name("debug", arch));
	Dictionary rinfo = find_export_template(get_template_file_name("release", arch));
    bool dvalid = dinfo["error_string"].operator String().is_empty();
    bool rvalid = rinfo["error_string"].operator String().is_empty(); 

	if (preset->get("custom_template/debug") != "") {
		dvalid = FileAccess::file_exists(preset->get("custom_template/debug"));
		if (!dvalid) {
			err += "Custom debug template not found.\n";
		}
	}
	if (preset->get("custom_template/release") != "") {
		rvalid = FileAccess::file_exists(preset->get("custom_template/release"));
		if (!rvalid) {
			err += "Custom release template not found.\n";
		}
	}

	valid = dvalid || rvalid;
	set_config_missing_templates(!valid);
    if (!valid) {
        if (!dvalid && !dinfo["error_string"].operator String().is_empty()) {
            err += dinfo["error_string"].operator String() + "\n";
        }
        if (!rvalid && !rinfo["error_string"].operator String().is_empty()) {
            err += rinfo["error_string"].operator String() + "\n";
        }
    }

	bool uses_s3tc_bptc = preset->get("texture_format/s3tc_bptc");
	bool uses_etc2_astc = preset->get("texture_format/etc2_astc");

	if (!uses_s3tc_bptc && !uses_etc2_astc) {
		valid = false;
		err += "A texture format must be selected to export the project. Please select at least one texture format.\n";
	}

    String s = preset->get("options/must_be_moo");
    if (s != "MOO!") {
        valid = false;
        err += "It's not \"MOO!\"!!!\n";
    }

	if (!err.is_empty()) {
        set_config_error(err);
	}
	return valid;
}

bool EditorExportPlatformTemplate::_has_valid_project_configuration(const Ref<EditorExportPreset> &preset) const {
    return true;
}

/**************************************************************************/
/* Project Export                                                         */
/**************************************************************************/

Error EditorExportPlatformTemplate::_save_file(const String &path, const PackedByteArray &data, int file_no, int total, const PackedStringArray &enc_in, const PackedStringArray &enc_ex, const PackedByteArray &key, const String &save_path) {
	// TODO Save file to the custom archive format.
    printf("    FILE: %d/%d %s (%lld) ==> %s\n", file_no, total, path.utf8().get_data(), data.size(), save_path.utf8().get_data());
    return OK;
}

Error EditorExportPlatformTemplate::_save_so(const String &path, const PackedStringArray &tags, const String &target_folder, const String &save_path) {
	// TODO Handle shared object file.
    printf("    SO: %s ==> %s\n", path.utf8().get_data(), save_path.utf8().get_data());
    return OK;
}

String EditorExportPlatformTemplate::get_template_file_name(const String &target, const String &arch) const {
	return "msdos_" + target + "." + arch;
}

Error EditorExportPlatformTemplate::_export_project(const Ref<EditorExportPreset> &preset, bool debug, const String &path, BitField<EditorExportPlatform::DebugFlags> flags) {
	// Find export template.
	String custom_debug = preset->get("custom_template/debug");
	String custom_release = preset->get("custom_template/release");

	String template_path = debug ? custom_debug : custom_release;

	template_path = template_path.strip_edges();

	if (template_path.is_empty()) {
		Dictionary tinfo = find_export_template(get_template_file_name(debug ? "debug" : "release", preset->get("binary_format/architecture")));
        template_path = tinfo["path"];
	}

	if (!template_path.is_empty()) {
		add_message(EXPORT_MESSAGE_ERROR, "Prepare Template", vformat("Template file not found: \"%s\".", template_path));
	}

	// TODO Extract and prepare export template files.

	String pck_path;
	if (preset->get("binary_format/embed_pck")) {
		pck_path = path;
	} else {
		pck_path = path.get_basename() + ".pck";
	}

	Error err = FAILED;
	if (preset->get("archive/use_custom_format").operator bool()) {
		// Use custom format and callbacks to save project data.
		err = export_project_files(preset, debug, Callable(this, "_save_file").bind(path), Callable(this, "_save_so").bind(path));
	} else {
		// Use built-in PCK file writer.
		Dictionary res = save_pack(preset, debug, pck_path, preset->get("binary_format/embed_pck"));

		err = (Error)res["result"].operator int();
		// Handle shared objects.
		const Array &so_files = res["so_files"];
		for (int i = 0; i < so_files.size(); i++) {
			const Dictionary &so_file = so_files[i];
			_save_so(so_file["path"], so_file["tags"], so_file["target_folder"], path);
		}
	}

	return err;
}

Error EditorExportPlatformTemplate::_export_pack(const Ref<EditorExportPreset> &preset, bool debug, const String &path, BitField<EditorExportPlatform::DebugFlags> flags) {
	// Use build-in PCK writer.
    Dictionary res = save_pack(preset, debug, path, false);
    return (Error)res["result"].operator int();
}

Error EditorExportPlatformTemplate::_export_zip(const Ref<EditorExportPreset> &preset, bool debug, const String &path, BitField<EditorExportPlatform::DebugFlags> flags) {
	// Use build-in ZIP writer.
    Dictionary res = save_zip(preset, debug, path);
    return (Error)res["result"].operator int();
}

/**************************************************************************/
/* One-click Deploy / Remote Debug                                        */
/**************************************************************************/

Ref<Texture2D> EditorExportPlatformTemplate::_get_run_icon() const {
    return run_icon;
}

bool EditorExportPlatformTemplate::_poll_export() {
	// Check if at least one export preset is set to runnable and remote debug is enabled.
	bool has_runnable_preset = false;
	Array presets = get_current_presets();
	for (int i = 0; i < presets.size(); i++) {
		const Ref<EditorExportPreset> &preset = presets[i];
		if (preset.is_valid() && preset->is_runnable() && preset->get("ssh_remote_deploy/enabled").operator bool()) {
			has_runnable_preset = true;
			break;
		}
	}

	int prev = menu_options;
	menu_options = (has_runnable_preset);
	if (ssh_pid != 0) {
		menu_options += 1; // Count "Stop" option.
	}
	// If number of menu option changed, update menu.
	return menu_options != prev;
}

int32_t EditorExportPlatformTemplate::_get_options_count() const {
    return menu_options;
}

String EditorExportPlatformTemplate::_get_options_tooltip() const {
    return "MS-DOS One Click Deploy";
}

Ref<ImageTexture> EditorExportPlatformTemplate::_get_option_icon(int32_t device) const {
    return (device) ? stop_icon : run_icon;
}

String EditorExportPlatformTemplate::_get_option_label(int32_t device) const {
    return (device) ? "Stop and uninstall" : "Run on remote DOS system";
}

String EditorExportPlatformTemplate::_get_option_tooltip(int32_t device) const {
    return (device) ? "Stop and uninstall running project from the remote system" : "Run exported project on remote DOS system";
}

String EditorExportPlatformTemplate::_get_device_architecture(int32_t device) const {
    return "x86_16";
}

void EditorExportPlatformTemplate::_cleanup() {
	// TODO. Stop remote.
	ssh_pid = 0;
}

Error EditorExportPlatformTemplate::_run(const Ref<EditorExportPreset> &preset, int32_t device, BitField<EditorExportPlatform::DebugFlags> debug_flags) {
	if (device) {
		// TODO Stop option selected.
		return OK;
	}

	// Export project to the temp location.
	const String dest = EditorInterface::get_singleton()->get_editor_paths()->get_cache_dir().path_join("dos");
	Ref<DirAccess> da = DirAccess::open(EditorInterface::get_singleton()->get_editor_paths()->get_cache_dir());
	if (da.is_valid() && !da->dir_exists(dest)) {
		Error err = da->make_dir_recursive(dest);
		if (err != OK) {
			return err;
		}
	}

	const String basepath = dest.path_join("tmp_dos_export");

	Error err = export_project(preset, true, basepath +  String(".zip"), debug_flags); // Note: call `export_project` not `_export_project` to ensure plugin notifier is initialized.
	if (err != OK) {
		return err;
	}

	// Generate command line arguments from the debug flags:
	PackedStringArray cmd_args_list = gen_export_flags(debug_flags);

	// Get remote debug settings.
	const bool use_remote = debug_flags.has_flag(DEBUG_FLAG_REMOTE_DEBUG) || debug_flags.has_flag(DEBUG_FLAG_DUMB_CLIENT);
	const int dbg_port = EditorInterface::get_singleton()->get_editor_settings()->get("network/debug/remote_port");

	// TODO Upload to the remote host
	// TODO Run on the remote host
    ssh_pid = 1000;

	return OK;
}
