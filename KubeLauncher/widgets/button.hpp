#pragma once
#include "ulix/element.hpp"
#include "ulix/log.hpp"
#include <ulix/align.hpp>
#include <ulix/cursor.hpp>
#include <ulix/color.hpp>
#include <ulix/effents.hpp>
#include <ulix/context.hpp>

namespace kl {
    struct button {
        ulx::clicked clicked_state;
        ulx::color empty_color;
        ulx::gradcolor background;
        ulx::element::event::mouse clicked_event;
        ulx::color pressed_color;
        ulx::color hovered_color;

        inline constexpr button(ulx::color&& start): background(start), empty_color(start) {}
        inline constexpr auto element(ulx::strvw id, 
            ulx::element::event::mouse&& clicked_event, 
            ulx::color&& pressed_color, ulx::color&& hovered_color
        ) -> ulx::element {
            this->clicked_event = clicked_event;
            this->pressed_color = pressed_color;
            this->hovered_color = hovered_color;

            auto obj = ulx::element::unbordered(id)
                .call([this](ulx::element& slf) {
                    clicked_state.usefor(slf, this->clicked_event, 
                        event_pressed [this](ulx::context& ctx, ulx::element& slf) {
                            background.pressed(slf, ulx::color{22, 22, 22, 255});
                            slf.back(background.to(
                                this->pressed_color, 0));
                            slf.cur(ulx::handcur);
                        }, event_released [this](ulx::context& ctx, ulx::element& slf) {
                            slf.back(background.to(
                                empty_color, 150));
                            slf.cur(ulx::resetcur);
                            background.released(slf, {22, 22, 22, 255});
                        }, event_hovered [this](ulx::context& ctx, ulx::element& slf) {
                            background.hovered(slf, ulx::color{22, 22, 22, 255});
                            slf.back(background.to(
                                this->hovered_color, 150));
                            slf.cur(ulx::handcur);
                        }
                    );
                });
            return obj;
        }
    };
}
