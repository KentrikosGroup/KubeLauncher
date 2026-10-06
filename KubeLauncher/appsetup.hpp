#pragma once

#include "ulix/align.hpp"
#include "ulix/present_mode.hpp"
#include <filesystem>
#include <ulix/ulix.hpp>
#include <ulix/extensions/az.comments.hpp>


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
    if (local_appdata.empty()) ulx::log::err("LOCALAPPDATA not set");

    std::filesystem::path cache_dir = std::filesystem::path(local_appdata) / "KubeLauncher" / "cache";
    std::error_code error_code;

    if (!std::filesystem::create_directories(cache_dir, error_code))
        if (error_code) ulx::log::err("Failed to create cache directory: {}", error_code.message());

    return cache_dir;
}

namespace appsetup {
    inline static ulx::wininfo window_info;
    inline static ulx::appinfo app_info;
    inline static ulx::renderinfo render_info;
    inline static std::filesystem::path cwd;
    inline static std::filesystem::path datas_dir;
    
    inline static constexpr auto svg(ulx::strvw name) {
        return ulx::file((datas_dir / "images" / "svgs" / name).string());
    }

    inline void init(char* argv[], ulx::arr<ulx::u32, 3> version, ulx::context::render_callback render_callback) {
        cwd = std::filesystem::path(argv[0]).parent_path();
        datas_dir = cwd / "datas";

        window_info = ulx::wininfo("KubeLauncher", "KubeLauncherWindowClass")
            .unattr(ulx::winattr::titled)
            .size(ulx::recsize::from_ratio(ulx::screen::width() * 0.8f, 0.625f))
            .min(ulx::recsize::from_ratio(ulx::screen::width() * 0.8f, 0.625f))
            .max(ulx::screen::size())
            .vtitlebar(40.0f).vclose(48.5f)
            .vmin(48.5f).vmax(48.5f);
        app_info = ulx::appinfo("KubeLauncher", (get_cache_path() / "cache.bin").string())
            .version(version[0], version[1], version[2])
            .icon((datas_dir / "images" / "icon.ico").string());
        render_info = ulx::renderinfo(render_callback)
            .present_mode(ulx::immediatemode)
            .max_textures(65535);
    }

    inline int exec(ulx::u64 delay, ulx::context::tick_callback tick) {
        ulx::context ctx = ulx::context(app_info, window_info, render_info);
        ctx.mov(ulx::recpos(
            (ulx::screen::width() - ctx.width()) / 2,
            (ulx::screen::height() - ctx.height()) / 2
        ));
        ctx.set_tick(tick);
        ctx.set_delay(delay);

        ctx.show();
        return ctx.exec();
    }
}
