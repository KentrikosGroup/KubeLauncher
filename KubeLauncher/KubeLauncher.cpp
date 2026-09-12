// #define ULIXRELEASEAPPLICATION
#include "appsetup.hpp"

auto render_objects([[maybe_unused]] UContext& ctx) -> ulx::scene {
    static int i = 0;
    i++;

    return ulx::scene()
        .background(ulx::color(25, 25, 25))
        .layout(ulx::layout::ver)
        .vpadding(5)
        .hpadding(5)

        .child(ulx::object("vulkan_image_container")
            .rect(ulx::rect(0, 0, ulx::rect::fullsize, ulx::rect::fullsize))
            .border(ulx::anchor::all, 0)
            .corner(ulx::anchor::all, 5)
            .fill(ulx::anchor::all, ulx::color(0, 0, 0))
            .texture(ulx::file("KubeLauncher/vulkan.png"))

            .child(ulx::object("hello_container")
                .rect(ulx::rect(10, 10, ulx::rect::autosize, ulx::rect::autosize))
                .fill(ulx::anchor::all, ulx::color(0, 0, 0))
                .texture(std::to_string(i), ulx::font().color(ulx::color(255, 255, 255)).size(64).scale(2))
                .corner(ulx::anchor::all, 0)
                .border(ulx::anchor::all, 1.5)
                .border(ulx::anchor::topleft, ulx::color(255, 255, 0))
                .border(ulx::anchor::topright, ulx::color(255, 0, 0))
                .border(ulx::anchor::bottomleft, ulx::color(0, 255, 0))
                .border(ulx::anchor::bottomright, ulx::color(0, 0, 255))

                .child(ulx::object("world_container")
                    .rect(ulx::rect(75, 0, ulx::rect::autosize, ulx::rect::autosize))
                    .fill(ulx::anchor::all, ulx::color(0, 0, 0))
                    .texture("World!", ulx::font().color(ulx::color(255, 255, 255)).size(64).scale(2))
                    .corner(ulx::anchor::all, 0)
                    .border(ulx::anchor::all, 0)
                )
            )
        );
}

auto main() -> int {
    appsetup::init({0, 1, 5}, render_objects);
    return appsetup::exec(UContext::TickTimer());
}
