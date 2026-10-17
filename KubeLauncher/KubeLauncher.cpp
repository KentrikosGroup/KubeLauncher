// #define ULIXRELEASE

#include "ulix/__class_decl/context.hpp"
#include "ulix/align.hpp"
#include "ulix/box.hpp"
#include "appsetup.hpp"
#include "ulix/color.hpp"
#include "ulix/element.hpp"
#include "ulix/point.hpp"
#include "ulix/size.hpp"
#include "ulix/wstates.hpp"
#include "widgets/button.hpp"

struct wstates {
    struct titlebar {
        inline static auto close_button = kl::button{ulx::color(22, 22, 22)};
        inline static auto max_button = kl::button{ulx::color(22, 22, 22)};
        inline static auto min_button = kl::button{ulx::color(22, 22, 22)};
    };
};

auto render(ulx::context& ctx) -> ulx::scene {
    return ulx::scene()
        .back({22, 22, 22})
        .box(ulx::verbox).pad(0)
        .child(ulx::element::unbordered("titlebar")
            .size(ulx::size::fullw(40.0f))
            .child(wstates::titlebar::close_button.element("close_button", 
                event_pressed [](ulx::context& ctx, ulx::element& slf) {
                    ctx.exit();
                }, ulx::color(196, 43, 28, 240), ulx::color(196, 43, 28, 255))
                .size({48.5f, 40.0f})
                .child(ulx::element::unvisible("icon", ulx::geom({25, 25}, {11.75f, 7.5f}))
                    .texture(appsetup::svg("close.svg"), {25, 25})
                )
            )
            .child(wstates::titlebar::max_button.element("max_button", 
                event_pressed [](ulx::context& ctx, ulx::element& slf) {
                    if (ctx.is_maxed()) {
                        ctx.restore();
                        return;
                    } ctx.max();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 250))
                .size({48.5f, 40.0f})

                .when(ctx.is_maxed(), event_when [](ulx::element& slf) {
                    slf.child(ulx::element::unvisible("icon", ulx::geom({25, 25}, {11.75f, 7.5f}))
                        .texture(appsetup::svg("restore.svg"), {25, 25})
                    );
                }, event_else [](ulx::element& slf) {
                    slf.child(ulx::element::unvisible("icon", ulx::geom({25, 25}, {11.75f, 7.5f}))
                        .texture(appsetup::svg("rectangle.svg"), {25, 25})
                    );
                })
            )
            .child(wstates::titlebar::min_button.element("min_button", 
                event_pressed [](ulx::context& ctx, ulx::element& slf) {
                    ctx.min();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 250))
                .size({48.5f, 40.0f})
                .child(ulx::element::unvisible("icon", ulx::geom({25, 25}, {11.75f, 7.5f}))
                    .texture(appsetup::svg("minimize.svg"), {25, 25})
                )
            )

            .back({22, 22, 22})
            .layout({
                .box = ulx::horbox,
                .align = ulx::alignright,
                .padding = 0,
            })
        );
}

auto main(int argc, char* argv[]) -> int {
    appsetup::init(argv, {0, 0, 13}, render);
    return appsetup::exec(0, {});
}
