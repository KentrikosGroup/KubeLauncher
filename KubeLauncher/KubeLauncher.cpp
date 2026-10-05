// #define ULIXRELEASE

#include "ulix/__class_decl/context.hpp"
#include "ulix/align.hpp"
#include "ulix/font.hpp"
#include "ulix/box.hpp"
#include "appsetup.hpp"
#include "ulix/color.hpp"
#include "ulix/object.hpp"
#include "ulix/recpos.hpp"
#include "ulix/recsize.hpp"
#include "ulix/wstates.hpp"
#include "widgets/button.hpp"

struct wstates {
    struct titlebar {
        inline static auto close_button = kl::button{ulx::color(22, 22, 22, 255)};
        inline static auto max_button = kl::button{ulx::color(22, 22, 22, 255)};
        inline static auto min_button = kl::button{ulx::color(22, 22, 22, 255)};
    };

    inline static constexpr void init() {
    }
};

auto render(ulx::context& ctx) -> ulx::scene {
    kl::button::start();
    auto scene = ulx::scene()
        .back({22, 22, 22})
        .box(ulx::verbox).pad(0)
        .child(ulx::object::unbordered("titlebar")
            .size(ulx::recsize::fullw(40.0f))
            .child(wstates::titlebar::close_button.object("close_button", 
                event_pressed [](ulx::context& ctx, ulx::object& slf) {
                    ctx.exit();
                }, ulx::color(196, 43, 28, 240), ulx::color(196, 43, 28, 255))
                .size({48.5f, 40.0f})
                .child(ulx::object::unvisible("icon", ulx::geom({25, 25}, {11.75f, 7.5f}))
                    .texture(appsetup::svg("close.svg"), {25, 25})
                )
            )
            .child(wstates::titlebar::max_button.object("max_button", 
                event_pressed [](ulx::context& ctx, ulx::object& slf) {
                    if (ctx.is_maxed()) {
                        ctx.restore();
                        return;
                    }
                    ctx.max();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 250))
                .size({48.5f, 40.0f})
                .child(ulx::object::unvisible("icon", ulx::geom({25, 25}, {11.75f, 7.5f}))
                    .texture(appsetup::svg("rectangle.svg"), {25, 25})
                )
            )
            .child(wstates::titlebar::min_button.object("min_button", 
                event_pressed [](ulx::context& ctx, ulx::object& slf) {
                    ctx.min();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 250))
                .size({48.5f, 40.0f})
                .child(ulx::object::unvisible("icon", ulx::geom({25, 25}, {11.75f, 7.5f}))
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
    kl::button::end(ctx);

    return scene;
}

auto main(int argc, char* argv[]) -> int {
    wstates::init();
    appsetup::init(argv, {0, 0, 11}, render);
    return appsetup::exec(0, {});
}

// v0.0.5: Updated ulx::object::{released, pressed, hovered}
// v0.0.6: Updated ulx::object::text() multi-object texture hits
// v0.0.7: Updated tick_callback single callback
// v0.0.8: Updated vertex_buffer, index_buffer, texture_buffer inertia growth
// v0.0.9: Some minor optimizations
// v0.0.10: Updated ulx::object::call cast to lvalue, ulx::wst::clicked
// v0.0.11: Updated ulx::wst::gradcolor gradent color
// v0.0.12: Updated topbar dragging, button effents
// v0.0.13: Updated native win32 topbar & buttons 
