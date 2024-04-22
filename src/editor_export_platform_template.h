#ifndef EDITOR_EXPORT_PLATFORM_TEMPLATE_H
#define EDITOR_EXPORT_PLATFORM_TEMPLATE_H

#include <godot_cpp/classes/global_constants.hpp>

#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/editor_export_platform.hpp>
#include <godot_cpp/classes/editor_export_platform_extension.hpp>
#include <godot_cpp/classes/editor_export_preset.hpp>
#include <godot_cpp/classes/editor_settings.hpp>
#include <godot_cpp/classes/editor_paths.hpp>
#include <godot_cpp/classes/script_editor.hpp>
#include <godot_cpp/classes/os.hpp>

#include <godot_cpp/classes/texture.hpp>
#include <godot_cpp/classes/theme.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/variant/variant.hpp>

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

class EditorExportPlatformTemplate : public EditorExportPlatformExtension {
    GDCLASS(EditorExportPlatformTemplate, EditorExportPlatformExtension);

    Ref<ImageTexture> logo;
	Ref<ImageTexture> run_icon;
	Ref<ImageTexture> stop_icon;

	int ssh_pid = 0;
	int menu_options = 0;

protected:
    static void _bind_methods();

    String get_template_file_name(const String &target, const String &arch) const;

    Error _save_file(const String &path, const PackedByteArray &data, int file_no, int total, const PackedStringArray &enc_in, const PackedStringArray &enc_ex, const PackedByteArray &key, const String &save_path);
    Error _save_so(const String &path,  const PackedStringArray &tags, const String &target_folder, const String &save_path);

public:
    virtual PackedStringArray _get_preset_features(const Ref<EditorExportPreset> &preset) const override;
    virtual bool _is_executable(const String &path) const override;
    virtual TypedArray<Dictionary> _get_export_options() const override;
    virtual bool _should_update_export_options() override;
    virtual bool _get_export_option_visibility(const Ref<EditorExportPreset> &preset, const String &option) const override;
    virtual String _get_export_option_warning(const Ref<EditorExportPreset> &preset, const StringName &option) const override;
    virtual String _get_os_name() const override;
    virtual String _get_name() const override;
    virtual Ref<Texture2D> _get_logo() const override;
    virtual bool _poll_export() override;
    virtual int32_t _get_options_count() const override;
    virtual String _get_options_tooltip() const override;
    virtual Ref<ImageTexture> _get_option_icon(int32_t device) const override;
    virtual String _get_option_label(int32_t device) const override;
    virtual String _get_option_tooltip(int32_t device) const override;
    virtual String _get_device_architecture(int32_t device) const override;
    virtual void _cleanup() override;
    virtual Error _run(const Ref<EditorExportPreset> &preset, int32_t device, BitField<EditorExportPlatform::DebugFlags> debug_flags) override;
    virtual Ref<Texture2D> _get_run_icon() const override;
    virtual bool _can_export(const Ref<EditorExportPreset> &preset, bool debug) const override;
    virtual bool _has_valid_export_configuration(const Ref<EditorExportPreset> &preset, bool debug) const override;
    virtual bool _has_valid_project_configuration(const Ref<EditorExportPreset> &preset) const override;
    virtual PackedStringArray _get_binary_extensions(const Ref<EditorExportPreset> &preset) const override;
    virtual Error _export_project(const Ref<EditorExportPreset> &preset, bool debug, const String &path, BitField<EditorExportPlatform::DebugFlags> flags) override;
    virtual Error _export_pack(const Ref<EditorExportPreset> &preset, bool debug, const String &path, BitField<EditorExportPlatform::DebugFlags> flags) override;
    virtual Error _export_zip(const Ref<EditorExportPreset> &preset, bool debug, const String &path, BitField<EditorExportPlatform::DebugFlags> flags) override;
    virtual PackedStringArray _get_platform_features() const override;

    EditorExportPlatformTemplate();
    ~EditorExportPlatformTemplate() {}
};

#endif // EDITOR_EXPORT_PLATFORM_TEMPLATE_H
