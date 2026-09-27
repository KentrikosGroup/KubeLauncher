#define ULIXRELEASE

#include "ulix/align.hpp"
#include "ulix/layout.hpp"
#include "appsetup.hpp"
#include "ulix/color.hpp"
#include "ulix/object.hpp"

auto render([[maybe_unused]] ulx::context& ctx) -> ulx::scene {
    return ulx::scene()
        .background(ulx::color(25, 25, 25))
        .align(ulx::alignleft | ulx::aligntop)
        .padding(5).layout(ulx::horbox)

        .child(ulx::object()
            .size(ulx::recsize(50, 50))
            .background(ulx::color::empty())
            .border(ulx::color(0, 255, 0))
            .layout(ulx::verbox).padding(20)
            .align(ulx::alignleft | ulx::alignbottom)
            
            .child(ulx::object()
                .size(ulx::recsize(20, 20))
                .background(ulx::color::empty())
                .border(ulx::color(0, 0, 255))
                .corner(5)
            ).child(ulx::object()
                .size(ulx::recsize(20, 20))
                .background(ulx::color::empty())
                .border(ulx::color(255, 255, 255))
                .corner(5)
            )
        ).child(ulx::object()
            .size(ulx::recsize(50, 50))
            .background(ulx::color::empty())
            .border(ulx::color(255, 0, 0))
        );
}

auto main() -> int {
    appsetup::init({0, 1, 5}, render);
    return appsetup::exec(ulx::context::ticktimer());
}
