// #define ULIXRELEASE
#include "appsetup.hpp"
#include "ulix/color.hpp"
#include "ulix/element.hpp"
#include "ulix/types.hpp"

#include <ulix/gradbutton.hpp>

inline static auto Microsoft_Yahei = ulx::font("msyh.ttc");

inline static auto close_button = ulx::gradbutton(ulx::color(22, 22, 22));
inline static auto max_button = ulx::gradbutton(ulx::color(22, 22, 22));
inline static auto min_button = ulx::gradbutton(ulx::color(22, 22, 22));

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
                .icon("icon", kl::svg("close.svg"), {25, 25})
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
                    slf.icon("icon", kl::svg("restore.svg"), {25, 25});
                }, event_else [](ulx::element& slf) {
                    slf.icon("icon", kl::svg("rectangle.svg"), {25, 25});
                })
            )
            .child(min_button.element("min_button",
                event_pressed [](ulx::context& ctx, ulx::element& slf) {
                    ctx.win_min();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 250))
                .size({48.5f, 40.0f})
                .icon("icon", kl::svg("minimize.svg"), {25, 25})
            )

            .back({22, 22, 22})
            .layout({
                .box = ulx::horbox,
                .align = ulx::alignright,
                .padding = 0,
            })
        )
        .child(ulx::element("c", "Test"));
}

auto main(int argc, char* argv[]) -> int {
    kl::init(argv, {0, 0, 25}, render);
    return kl::exec(0, {});
}
