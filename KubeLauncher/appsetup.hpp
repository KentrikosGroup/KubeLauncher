#pragma once

#include <filesystem>
#include <print>
#include <ulix/context.hpp>
#include <ulix/screen.hpp>
#include <ulix/extensions/az.comments.hpp>

namespace kl {
    inline static constexpr auto showerr(ulx::stablestr<> info) {
        std::println("\x1b[91mKubeLauncher Error:\x1b[0m {}", info);
    }
    
    inline static constexpr auto ensure_cachedir_exists(ulx::path cwd) -> void {
        auto cache_path = cwd.with("cache");
        if (cache_path.exists()) return;
        if (!std::filesystem::create_directory(cache_path.str().cstr())) 
            showerr("failed to make cache directory");
    }
    
    inline static ulx::wininfo window_info;
    inline static ulx::appinfo app_info;
    inline static ulx::renderinfo render_info;
    inline static ulx::path cwd;
    inline static ulx::path datas_dir;
    
    inline static constexpr auto svg(ulx::strvw name) -> ulx::path {
        return datas_dir.with("images", "svgs", name).str();
    }

    inline void init(char* argv[], ulx::arr<ulx::u32, 3> version, ulx::context::rendercallback render_callback) {
        cwd = ulx::path(argv[0]).parent();
        datas_dir = cwd.with("datas");

        ensure_cachedir_exists(cwd);
        window_info = ulx::wininfo("KubeLauncher", "KubeLauncherWindowClass")
            .unattr(ulx::winattr::titledattr)
            .size(ulx::size::from_ratio(ulx::screen::width() * 0.8f, 0.625f))
            .min(ulx::size::from_ratio(ulx::screen::width() * 0.8f, 0.625f))
            .max(ulx::screen::size())
            .vtitlebar(40.0f).vclose(48.5f)
            .vmin(48.5f).vmax(48.5f);
        app_info = ulx::appinfo("KubeLauncher", cwd.with("cache"))
            .version(version[0], version[1], version[2])
            .icon(datas_dir.with("images", "icon.ico"));
        render_info = ulx::renderinfo(render_callback);
    }

    inline int exec(ulx::u64 delay, ulx::context::tickcallback tick) {
        ulx::context ctx = ulx::context(app_info, window_info, render_info);
        ctx.win_move(ulx::point::center_to(ctx.win_size(), ulx::screen::size()));
        ctx.set_tick(tick, delay);

        ctx.win_show();
        return ctx.exec();
    }
}
