#pragma once

#include "ulix/recsize.hpp"
#include "ulix/screen.hpp"
#include <print>
#include <ulix/ulix.hpp>
#include <ulix/extensions/az__pragma_comments.hpp>


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
    inline ulx::wininfo window_info;
    inline ulx::appinfo app_info;
    inline ulx::renderinfo render_info;

    inline void init(ulx::arr<ulx::u32, 3> version, ulx::context::render_callback render_callback) {
        window_info = ulx::wininfo("KubeLauncher", "KubeLauncherWindowClass")
            .unattr(ulx::winattr::titled)
            .size(ulx::recsize::from_ratio(ulx::screen::width() * 0.8f, 0.625f))
            .min(ulx::recsize::from_ratio(ulx::screen::width() * 0.8f, 0.625f))
            .max(ulx::screen::size());
        app_info = ulx::appinfo("KubeLauncher", (get_cache_path() / "cache.bin").string())
            .version(version[0], version[1], version[2]);
        render_info = ulx::renderinfo(render_callback);
    }

    inline int exec(ulx::context::ticktimer tick_timer) {
        ulx::context ctx = ulx::context(app_info, window_info, render_info);
        ctx.set_pos(ulx::recpos(
            (ulx::screen::width() - ctx.width()) / 2,
            (ulx::screen::height() - ctx.height()) / 2
        ));
        ctx.set_timer(tick_timer);

        ctx.show();
        return ctx.exec();
    }
}
