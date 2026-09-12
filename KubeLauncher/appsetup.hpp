#pragma once

#include <ulix/ulix.hpp>
#include <ulix/extensions/az__pragma_comments.hpp>


#ifdef NDEBUG
    inline constexpr bool enabled_vulkan_debug = false;
#else
    inline constexpr bool enabled_vulkan_debug = true;
#endif


static ulx::str get_env(const char* name) {
    char* buffer = nullptr;
    size_t size = 0;
    _dupenv_s(&buffer, &size, name);
    if (!buffer) return {};
    ulx::str value = ulx::str(buffer);
    free(buffer);
    return value;
}

inline std::filesystem::path get_cache_path() {
    ulx::str local_appdata = get_env("LOCALAPPDATA");
    if (local_appdata.empty()) ulx::log::ulixerr("LOCALAPPDATA not set");

    std::filesystem::path cache_dir = std::filesystem::path(local_appdata) / "AzLauncher" / "cache";
    std::error_code error_code;

    if (!std::filesystem::create_directories(cache_dir, error_code))
        if (error_code) ulx::log::ulixerr("Failed to create cache directory: {}", error_code.message());

    return cache_dir;
}

namespace appsetup {
    inline ulx::wininfo window_info;
    inline ulx::appinfo app_info;
    inline ulx::renderinfo render_info;

    inline void init(ulx::arr<ulx::u32, 3> version, UContext::RenderCallback render_callback) {
        UContext::init();

        window_info = ulx::wininfo("AzLauncher", "AzLauncherWindowClass")
            .unattrs(ulx::winattr::Titled)
            .rect(ulx::screen::get_rect().new_with_widthper(0.8, 0.625))
            .min_rect(ulx::screen::get_rect().new_with_widthper(0.6, 0.625))
            .max_rect(ulx::screen::get_rect());
        app_info = ulx::appinfo("AzLauncher", (get_cache_path() / "cache.bin").string())
            .version(version[0], version[1], version[2])
            .vkdbg(enabled_vulkan_debug);
        render_info = ulx::renderinfo(render_callback);
    }

    inline int exec(UContext::TickTimer tick_timer) {
        UContext ctx = UContext(app_info, window_info, render_info);
        ctx.set_rect(ulx::screen::get_rect().new_center(ctx.rect()));
        ctx.set_timer(tick_timer);

        ctx.show();
        return ctx.exec();
    }
}
