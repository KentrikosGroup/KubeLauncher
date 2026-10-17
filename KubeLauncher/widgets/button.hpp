#pragma once
#include "ulix/element.hpp"
#include <ulix/align.hpp>
#include <ulix/cursor.hpp>
#include <ulix/color.hpp>
#include <ulix/requires.hpp>
#include <ulix/wstates.hpp>
#include <ulix/context.hpp>
#include <utility>

namespace kl {
    struct button {
        ulx::wst::clicked clicked;
        ulx::color empty_color;
        ulx::wst::gradcolor background;
        ulx::element::mouse_event clicked_e;
        ulx::color pressed_color_;
        ulx::color hovered_color_;

        template<typename C>
            requires ulx::expect<C, ulx::color>
        inline constexpr button(C&& start): background(std::forward<C>(start)), empty_color(std::forward<C>(start)) {}
        
        template<typename C, typename PC, typename HC>
            requires ulx::expect<C, ulx::element::mouse_event> &&

                     ulx::expect<PC, ulx::color> &&
                     ulx::expect<HC, ulx::color>
        inline constexpr auto element(ulx::strvw id, C&& clicked_event, PC&& pressed_color, HC&& hovered_color) -> ulx::element {
            clicked_e = std::forward<C>(clicked_event);
            pressed_color_ = std::forward<PC>(pressed_color);
            hovered_color_ = std::forward<HC>(hovered_color);

            auto obj = ulx::element::unbordered(id)
                .call([this](ulx::element& slf) {
                    clicked.usefor(slf,
                        clicked_e, event_pressed [this](ulx::context& ctx, ulx::element& slf) {
                            background.pressed(slf, {22, 22, 22, 255});
                            slf.back(background.to(
                                pressed_color_, 0));
                            slf.cur(ulx::handcur);
                        }, event_released [this](ulx::context& ctx, ulx::element& slf) {
                            slf.back(background.to(
                                empty_color, 150));
                            slf.cur(ulx::resetcur);
                            background.released(slf, {22, 22, 22, 255});
                        }, event_hovered [this](ulx::context& ctx, ulx::element& slf) {
                            background.hovered(slf, {22, 22, 22, 255});
                            slf.back(background.to(
                                hovered_color_, 150));
                            slf.cur(ulx::handcur);
                        }
                    );
                });
            return obj;
        }
    };
}
