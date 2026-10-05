#pragma once
#include "ulix/object.hpp"
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
        ulx::object::mouse_event clicked_e;
        ulx::color pressed_color_;
        ulx::color hovered_color_;

        inline static ulx::u64 handed_buttons = 0;
        inline static bool is_hand;

        template<typename C>
            requires ulx::expect<C, ulx::color>
        inline constexpr button(C&& start): background(std::forward<C>(start)), empty_color(std::forward<C>(start)) {}

        inline static constexpr auto start() -> void {
            handed_buttons = 0;
        }

        inline static constexpr auto end(ulx::context& ctx) -> void {
            if (kl::button::handed_buttons == 0) {
                ctx.set_cur(ulx::resetcur);
            }
        }
        
        template<typename C, typename PC, typename HC>
            requires ulx::expect<C, ulx::object::mouse_event> &&

                     ulx::expect<PC, ulx::color> &&
                     ulx::expect<HC, ulx::color>
        inline constexpr auto object(ulx::strvw id, C&& clicked_event, PC&& pressed_color, HC&& hovered_color) -> ulx::object {
            clicked_e = std::forward<C>(clicked_event);
            pressed_color_ = std::forward<PC>(pressed_color);
            hovered_color_ = std::forward<HC>(hovered_color);

            is_hand = false;
            auto obj = ulx::object::unbordered(id)
                .call([this](ulx::object& slf) {
                    clicked.usefor(slf,
                        clicked_e, event_pressed [this](ulx::context& ctx, ulx::object& slf) {
                            background.pressed(slf, {22, 22, 22, 255});
                            slf.back(background.to(
                                pressed_color_, 0));
                            ctx.set_cur(ulx::handcur); is_hand = true;
                        }, event_released [this](ulx::context& ctx, ulx::object& slf) {
                            slf.back(background.to(
                                empty_color, 150));
                            handed_buttons--;
                            background.released(slf, {22, 22, 22, 255});
                        }, event_hovered [this](ulx::context& ctx, ulx::object& slf) {
                            background.hovered(slf, {22, 22, 22, 255});
                            slf.back(background.to(
                                hovered_color_, 150));
                            ctx.set_cur(ulx::handcur); is_hand = true;
                        }
                    );
                });
            if (is_hand) handed_buttons++;
            return obj;
        }
    };
}
