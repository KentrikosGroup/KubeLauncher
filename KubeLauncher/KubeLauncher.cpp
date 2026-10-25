// #define ULIXRELEASE

#include "ulix/__class_decl/context.hpp"
#include "ulix/align.hpp"
#include "ulix/box.hpp"
#include "appsetup.hpp"
#include "ulix/color.hpp"
#include "ulix/element.hpp"
#include "ulix/font.hpp"
#include "ulix/point.hpp"
#include "ulix/size.hpp"
#include "ulix/wstates.hpp"
#include "widgets/button.hpp"

inline static auto Microsoft_Yahei = ulx::font(R"(D:\KubeLauncher\KubeLauncher\Microsoft YaHei.ttf)");

inline static auto close_button = kl::button{ulx::color(22, 22, 22)};
inline static auto max_button = kl::button{ulx::color(22, 22, 22)};
inline static auto min_button = kl::button{ulx::color(22, 22, 22)};

auto render(ulx::context& ctx) -> ulx::scene {
    return ulx::scene()
        .back({22, 22, 22})
        .box(ulx::verbox).pad(0)
        .child(ulx::element::unbordered("titlebar")
            .size(ulx::size::fullw(40.0f))
            .child(close_button.element("close_button",
                event_pressed [](ulx::context& ctx, ulx::element& slf) {
                    ctx.exit();
                }, ulx::color(196, 43, 28, 240), ulx::color(196, 43, 28, 255))
                .size({48.5f, 40.0f})
                .icon("icon", appsetup::svg("close.svg"), ulx::geom({25, 25}, {11.75f, 7.5f}))
            )
            .child(max_button.element("max_button",
                event_pressed [](ulx::context& ctx, ulx::element& slf) {
                    if (ctx.win_maxed()) {
                        ctx.win_restore();
                        return;
                    } ctx.win_max();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 250))
                .size({48.5f, 40.0f})

                .when(ctx.win_maxed(), event_when [](ulx::element& slf) {
                    slf.icon("icon", appsetup::svg("restore.svg"), ulx::geom({25, 25}, {11.75f, 7.5f}));
                }, event_else [](ulx::element& slf) {
                    slf.icon("icon", appsetup::svg("rectangle.svg"), ulx::geom({25, 25}, {11.75f, 7.5f}));
                })
            )
            .child(min_button.element("min_button",
                event_pressed [](ulx::context& ctx, ulx::element& slf) {
                    ctx.win_min();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 250))
                .size({48.5f, 40.0f})
                .icon("icon", appsetup::svg("minimize.svg"), ulx::geom({25, 25}, {11.75f, 7.5f}))
            )

            .back({22, 22, 22})
            .layout({
                .box = ulx::horbox,
                .align = ulx::alignright,
                .padding = 0,
            })
        )
        .child(ulx::element("english", "This is English"))
        .child(ulx::element("chinese", "中文", Microsoft_Yahei.make()));
}

auto main(int argc, char* argv[]) -> int {
    appsetup::init(argv, {0, 0, 13}, render);
    return appsetup::exec(0, {});
}
