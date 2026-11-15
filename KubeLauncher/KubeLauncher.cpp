// #define ULIXRELEASE
#include "appsetup.hpp"
#include "ulix/align.hpp"
#include "ulix/box.hpp"
#include "ulix/element.hpp"

#include <ulix/gradbutton.hpp>
#include <ulix/label.hpp>

inline static auto Microsoft_Yahei = ulx::font("msyh.ttc");

inline static auto close_button = ulx::gradbutton("close_button", ulx::color(22, 22, 22));
inline static auto max_button = ulx::gradbutton("max_button", ulx::color(22, 22, 22));
inline static auto min_button = ulx::gradbutton("min_button", ulx::color(22, 22, 22));

auto render(ulx::context& ctx) -> ulx::scene {
    return ulx::scene()
        .back({22, 22, 22})
        .box(ulx::verbox)
        .align(ulx::aligntop)
        .pad(0)
        
        .child(ulx::element("titlebar")
            .size(ulx::size::fullw(40.0f))
            .child(close_button.create(
                [] ulx_lambda_pressed {
                    ctx.exit();
                }, ulx::color(196, 43, 28, 240), ulx::color(196, 43, 28, 255))
                .size({48.5f, 40.0f})
                .icon("icon", kl::svg("close.svg"), {25, 25})
            )
            .child(max_button.create(
                [] ulx_lambda_pressed {
                    if (ctx.win_maxed()) {
                        ctx.win_restore();
                        return;
                    } ctx.win_max();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 225))
                .size({48.5f, 40.0f})

                .when(ctx.win_maxed(), 
                    [] ulx_lambda_when { slf.icon("icon", kl::svg("restore.svg"), {25, 25}); }, 
                    [] ulx_lambda_else { slf.icon("icon", kl::svg("rectangle.svg"), {25, 25}); }
                )
            )
            .child(min_button.create(
                [] ulx_lambda_pressed {
                    ctx.win_min();
                }, ulx::color(60, 60, 60, 240), ulx::color(60, 60, 60, 225))
                .size({48.5f, 40.0f})
                .icon("icon", kl::svg("minimize.svg"), {25, 25})
            )

            .back({22, 22, 22})
            .box(ulx::horbox).align(ulx::alignright)
        )
        .child(ulx::label("hello", "Hello, KubeLauncher!", Microsoft_Yahei));
}

auto main(int argc, char* argv[]) -> int {
    kl::init(argv, render);
    return kl::exec(0, {});
}
