// #define ULIXRELEASEAPPLICATION
#include <appsetup.hpp>

auto render_objects([[maybe_unused]] UContext& ctx) -> ulx::scene {
    static int i = 0;
    i++;
    
    return ulx::scene()
        .background(ulx::color(25, 25, 25))
        .layout(ulx::layout::Vertical)
        .vpadding(5)
        .hpadding(5)

        .child(ulx::object("vulkan_image_container")
            .rect(ulx::rect(0, 0, ulx::rect::Full, ulx::rect::Full))
            .border(ulx::anchor::AllAnchor, 0)
            .corner(ulx::anchor::AllAnchor, 5)
            .fill(ulx::anchor::AllAnchor, ulx::color(0, 0, 0))
            .texture(ulx::file("AzLauncher/vulkan.png"))

            .child(ulx::object("hello_container")
                .rect(ulx::rect(10, 10, ulx::rect::Auto, ulx::rect::Auto))
                .fill(ulx::anchor::AllAnchor, ulx::color(0, 0, 0))
                .texture(std::to_string(i), ulx::font().color(ulx::color(255, 255, 255)).size(64).scale(2))
                .corner(ulx::anchor::AllAnchor, 0)
                .border(ulx::anchor::AllAnchor, 1.5)
                .border(ulx::anchor::TopLeft, ulx::color(255, 255, 0))
                .border(ulx::anchor::TopRight, ulx::color(255, 0, 0))
                .border(ulx::anchor::BottomLeft, ulx::color(0, 255, 0))
                .border(ulx::anchor::BottomRight, ulx::color(0, 0, 255))

                .child(ulx::object("world_container")
                    .rect(ulx::rect(75, 0, ulx::rect::Auto, ulx::rect::Auto))
                    .fill(ulx::anchor::AllAnchor, ulx::color(0, 0, 0))
                    .texture("World!", ulx::font().color(ulx::color(255, 255, 255)).size(64).scale(2))
                    .corner(ulx::anchor::AllAnchor, 0)
                    .border(ulx::anchor::AllAnchor, 0)
                )
            )
        );
}

auto main() -> int {
    appsetup::init({0, 0, 5}, render_objects);
    return appsetup::exec(UContext::TickTimer());
}
